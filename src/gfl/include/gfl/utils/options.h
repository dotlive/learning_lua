#ifndef _GFL_OPTIONS_H_
#define _GFL_OPTIONS_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>


namespace Mage
{
    class Options
    {
        typedef std::map<std::string, std::string> OptionData;
        typedef OptionData::iterator OptionDataIter;
        typedef OptionData::const_iterator OptionDataCiter;

    public:
        static void Load(const char* path);
        static const std::string& Query(const char* key);

    private:
        Options() {}

        static bool s_initialized;
        static OptionData m_data;
    };
}

#endif // _GFL_OPTIONS_H_
