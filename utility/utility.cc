#include "utility.hpp"

static double EPSILON = 1e-6;

using namespace std;

string uint_to_string(uint32_t u) {
    char tmp[40] = {0};
    sprintf(tmp, "%u", u);
    return string(tmp);
}

int string_to_integer(string str){
    int tmpresint = 0;
    sscanf(str.c_str(), "%d", &tmpresint);
    return tmpresint;
}


double string_to_double(string str){
    double tmpresdouble = 0.00;
    sscanf(str.c_str(), "%lf", &tmpresdouble);
    return tmpresdouble;
}


string trim_string_quotes(string str){
    if(str.length() < 2) {
        return 0;
    }
    int st = 0, ed = str.length();
    if(str[0] == '"') {
        st++;
        ed--;
    }
    if(str[str.length()-1] == '"') {
        ed--;
    }
    return str.substr(st, ed);
}

int extract_from_char_string(string chstr){
    if(chstr.length() < 2) return 0;
    return (unsigned char)(chstr[1]);
}

bool double_equal(double a, double b){
    if(((a-b) < EPSILON) || ((b-a) < EPSILON)) return true;
    return false;
}
