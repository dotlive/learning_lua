#include "gfl/utils/options.h"

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"


namespace Mage
{
    bool Options::s_initialized = false;
    Options::OptionData Options::m_data;

    void Options::Load(const char* path)
    {
        if (s_initialized)
        {
            return;
        }

        rapidxml::file<> fdoc(path);
        if (fdoc.size() == 0)
        {
            return;
        }

        rapidxml::xml_document<> doc;
        doc.parse<0>(fdoc.data());

        rapidxml::xml_node<> *root_node = doc.first_node();
        if (root_node != NULL)
        {
            for (rapidxml::xml_node<> *option_node = root_node->first_node();
            option_node != NULL;
                option_node = option_node->next_sibling())
            {
                const char* opt_key = option_node->first_attribute("key")->value();
                const char* opt_val = option_node->first_attribute("value")->value();
                m_data[opt_key] = opt_val;
            }
        }

        s_initialized = true;
    }

    const std::string& Options::Query(const char* key)
    {
        if (!s_initialized)
        {
            return "";
        }

        OptionDataCiter citer = m_data.find(key);
        if (citer == m_data.end())
        {
            return "";
        }

        return citer->second;
    }
}
