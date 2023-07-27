#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>
#include <list>
#include <map>

using namespace std;

class Translator {
public:
    Translator() = default;

    void Add(string_view source, string_view target)
    {
       fbase_.emplace(make_pair(source,target));
       bbase_.emplace(make_pair(target,source));
    }


    string_view TranslateForward(string_view source) const
    {
        using namespace std::literals;
        string_view s = ""sv;
        if (fbase_.count(static_cast<string>(source)))
        {
            return fbase_.at(static_cast<string>(source));
        }
        else
        {
            return s;
        }
    }

    string_view TranslateBackward(string_view target) const
    {
        using namespace std::literals;
        string_view s = ""sv;
        if (bbase_.count(static_cast<string>(target)))
        {
            return bbase_.at(static_cast<string>(target));
        }
        else
        {
            return s;
        }
    }

private:
    map<string, string> fbase_;
    map<string, string> bbase_;
};


void TestSimple() {
    Translator translator;
    translator.Add(string("okno"s), string("window"s));
    translator.Add(string("stol"s), string("table"s));

    assert(translator.TranslateForward("okno"s) == "window"s);
    assert(translator.TranslateBackward("table"s) == "stol"s);
    assert(translator.TranslateForward("table"s) == ""s);
}

int main() {
    TestSimple();
    return 0;
} 