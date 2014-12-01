#include "../../Parser/bytestring.hpp"
#include "test.hpp"

class BytestringTest : public Test {
    ByteString value;

    public:
    
    std::pair<bool, std::string> decode(const std::string& encoded) {
        char *buffer  = new char[encoded.size()];
        int index = 0;
        int length = static_cast<int>(encoded.size());
        memcpy(buffer, encoded.c_str(), encoded.size());
        bool ret = value.parse(buffer, index, length);
        return std::make_pair(ret, value.toString());    
    }

    BytestringTest() {
        test = {
            [&]() -> bool {
                return decode("5:berea") == std::make_pair(true,std::string("berea"));
            },
            [&]() -> bool {
                return decode("1:k") == std::make_pair(true,std::string("k"));
            },

            [&]() -> bool {
                return decode("3:fun") == std::make_pair(true,std::string("fun"));
            },

            [&]() -> bool {
                return decode("3fun").first == false;
            },
            [&]() -> bool {
                return decode("5:fun").first == false;
            }
 
        };
    }

    std::string getType() {
        return "ByteString";
    }

};
