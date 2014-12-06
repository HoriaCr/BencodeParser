#include "../../Parser/list.hpp"
#include "../../Parser/bytestring.hpp"
#include "../../Parser/integer.hpp"
#include "test.hpp"

class ListTest : public Test {
        List value;

    public:
     
    std::pair<bool, List> decode(const std::string& encoded) {
        char *buffer  = new char[encoded.size()];
        int index = 0;
        int length = static_cast<int>(encoded.size());
        //List value;
        memcpy(buffer, encoded.c_str(), encoded.size()); 
        bool ret = value.parse(buffer, index, length); 
        return std::make_pair(ret, value);    
    }

    ListTest() {
        test = {
            [&]() -> bool {
                BencodeType* str = new ByteString("berea");
                List ans(std::vector<BencodeType*>{str});
                return decode("l5:bereae") == std::make_pair(true, ans);
            },
            [&]() -> bool {
                BencodeType* val = new Integer(32);
                List ans(std::vector<BencodeType*>{val});
                return decode("li32ee") == std::make_pair(true, ans);
            },

            [&]() -> bool {
                BencodeType* val = new Integer(0);
                BencodeType* str = new ByteString("val");
                List ans(std::vector<BencodeType*>{str, val});
                return decode("l3:vali0ee") == std::make_pair(true, ans);
            },

            [&]() -> bool {
                List l;
                return decode("le") == std::make_pair(true, l);
            },
            [&]() -> bool {
                return decode("el").first == false;
            }
 
        };
    }

    std::string getType() {
        return "List";
    }
};

