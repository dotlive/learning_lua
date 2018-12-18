#include "custom_allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FREELIST_INDEX(bytes) ((bytes - size_t(1)) >> (int)ALIGN_SHIFT)
#define ROUND_UP(bytes) (((bytes) + (size_t)ALIGN - 1) & ~((size_t)ALIGN - 1)) 

custom_allocator::custom_allocator()
{
    first_chunk_ = NULL;
    ptr_free_start_ = NULL;
    ptr_free_end_ = NULL;
    memset(free_list_, 0, sizeof(free_list_));
}

custom_allocator::~custom_allocator()
{
    free_all();
}

void* custom_allocator::alloc(size_t size)
{
    if (0 == size)
    {
        return (void*)"";
    }

    if (size > (size_t)MAX_BYTES)
    {
        void* p = new char[size];

        if (NULL == p)
        {
            // ÉêÇëÄÚ´æÊ§°Ü
            printf("(custom_allocator::alloc)no enough memory, size:%d", (int)size);
            abort();
            return NULL;
        }

        return p;
    }
    else
    {
        alloc_obj_t** my_free_list = free_list_ + FREELIST_INDEX(size);
        alloc_obj_t* result = *my_free_list;

        if (result != NULL)
        {
            *my_free_list = result->free_list_link;
            return result;
        }
        else
        {
            return resize(size);
        }
    }
}

void custom_allocator::free(void* ptr, size_t size)
{
    if ((NULL == ptr) || (0 == size))
    {
        return;
    }

    if (size > (size_t)MAX_BYTES)
    {
        delete[](char*)ptr;
    }
    else
    {
        alloc_obj_t** my_free_list = free_list_ + FREELIST_INDEX(size);

        ((alloc_obj_t*)ptr)->free_list_link = *my_free_list;
        *my_free_list = (alloc_obj_t*)ptr;
    }
}

void custom_allocator::free_all()
{
    alloc_chunk_t* p = first_chunk_;
    alloc_chunk_t* t;

    while (p)
    {
        t = p;
        p = p->chunk_link;
        delete[](char*)t;
    }

    first_chunk_ = NULL;
}

size_t custom_allocator::get_pool_size() const
{
    size_t count = 0;
    alloc_chunk_t* p = first_chunk_;

    while (p)
    {
        count += p->chunk_size;
        p = p->chunk_link;
    }

    return count;
}

size_t custom_allocator::get_free_size() const
{
    size_t count = 0;

    for (size_t i = 0; i < FREELIST_NUM; ++i)
    {
        alloc_obj_t* p = free_list_[i];

        while (p)
        {
            count += (i + 1) * ALIGN;
            p = p->free_list_link;
        }
    }

    return count;
}

char* custom_allocator::chunk_alloc(size_t size, int& nobjs)
{
    size_t total_bytes = size * nobjs;
    size_t bytes_left = ptr_free_end_ - ptr_free_start_;

    if (bytes_left >= total_bytes)
    {
        char* result = ptr_free_start_;
        ptr_free_start_ += total_bytes;
        return result;
    }
    else if (bytes_left >= size)
    {
        nobjs = (int)(bytes_left / size);
        total_bytes = size * nobjs;
        char* result = ptr_free_start_;
        ptr_free_start_ += total_bytes;
        return result;
    }
    else
    {
        size_t bytes_to_get = 2 * total_bytes;

        if (bytes_left > 0)
        {
            alloc_obj_t** my_free_list =
                free_list_ + FREELIST_INDEX(bytes_left);

            ((alloc_obj_t*)ptr_free_start_)->free_list_link = *my_free_list;
            *my_free_list = (alloc_obj_t*)ptr_free_start_;
        }

        size_t mem_size = sizeof(alloc_chunk_t) + bytes_to_get;
        alloc_chunk_t* pChunk = (alloc_chunk_t*)new char[mem_size];

        if (NULL == pChunk)
        {
            // ÉêÇëÄÚ´æÊ§°Ü
            printf("(custom_allocator::chunk_alloc)no enough memory, size:%d", (int)mem_size);
            abort();
            return NULL;
        }

        pChunk->chunk_link = first_chunk_;
        pChunk->chunk_size = bytes_to_get;
        first_chunk_ = pChunk;
        ptr_free_start_ = (char*)pChunk + sizeof(alloc_chunk_t);
        ptr_free_end_ = ptr_free_start_ + bytes_to_get;
        return chunk_alloc(size, nobjs);
    }
}

void* custom_allocator::resize(size_t n)
{
    int nobjs = 20;

    n = ROUND_UP(n);

    char* chunk = chunk_alloc(n, nobjs);

    if (1 == nobjs)
    {
        return chunk;
    }

    alloc_obj_t** my_free_list = free_list_ + FREELIST_INDEX(n);
    alloc_obj_t* result = (alloc_obj_t*)chunk;
    alloc_obj_t* current_obj;
    alloc_obj_t* next_obj;

    *my_free_list = next_obj = (alloc_obj_t*)(chunk + n);

    for (int i = 1; ; ++i)
    {
        current_obj = next_obj;
        next_obj = (alloc_obj_t*)((char*)next_obj + n);

        if ((nobjs - 1) == i)
        {
            current_obj->free_list_link = NULL;
            break;
        }
        else
        {
            current_obj->free_list_link = next_obj;
        }
    }

    return result;
}
