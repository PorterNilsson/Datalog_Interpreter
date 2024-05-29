#include "Parameter.h"

Parameter::Parameter(string p) {
    this->p = p;
}

bool Parameter::IsConstant() {
    if (p[0] == '\'') {
        return 1;
    }
    else {
        return 0;
    }

}

string Parameter::ToString() {
    return p;
}

char Parameter::ToChar() {
    return p[0];
}