#include "../../Parser/list.hpp"
#include "../../Parser/bytestring.hpp"
#include "../../Parser/integer.hpp"
#include "test.hpp"

class ListTest : public Test {

    public:
    
        ListTest() {
            test = {
                [&]() -> bool {
                    BencodeType* str = new ByteString("berea");
                    List ans(std::vector<BencodeType*>{str});
                    return decode<List>("l5:bereae") == std::make_pair(true, ans);
                },
                [&]() -> bool {
                    BencodeType* val = new Integer(32);
                    List ans(std::vector<BencodeType*>{val});
                    return decode<List>("li32ee") == std::make_pair(true, ans);
                },

                [&]() -> bool {
                    BencodeType* val = new Integer(0);
                    BencodeType* str = new ByteString("val");
                    List ans(std::vector<BencodeType*>{str, val});
                    return decode<List>("l3:vali0ee") == std::make_pair(true, ans);
                },

                [&]() -> bool {
                    List l;
                    return decode<List>("le") == std::make_pair(true, l);
                },
                [&]() -> bool {
                    return decode<List>("el").first == false;
                }
     
            };
        }

        std::string getType() {
            return "List";
        }
};

