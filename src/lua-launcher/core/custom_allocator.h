#ifndef _CUSTOM_ALLOCATOR_H_
#define _CUSTOM_ALLOCATOR_H_

class custom_allocator
{
private:
    enum { ALIGN = 8 };
    enum { ALIGN_SHIFT = 3 };
    enum { MAX_BYTES = 128 };
    enum { FREELIST_NUM = 16 };

    struct alloc_obj_t
    {
        alloc_obj_t* free_list_link;
    };

    struct alloc_chunk_t
    {
        alloc_chunk_t* chunk_link;
        size_t chunk_size;
    };

public:
    custom_allocator();
    ~custom_allocator();

    void* alloc(size_t size);
    void free(void* ptr, size_t size);

    size_t get_pool_size() const;
    size_t get_free_size() const;

private:
    custom_allocator(const custom_allocator&);
    custom_allocator& operator=(const custom_allocator&);

    void free_all();
    char* chunk_alloc(size_t size, int& nobjs);
    void* resize(size_t n);

private:
    alloc_chunk_t* first_chunk_;
    alloc_obj_t* free_list_[FREELIST_NUM];
    char* ptr_free_start_;
    char* ptr_free_end_;
};

#endif // _CUSTOM_ALLOCATOR_H_

