#include <convert.h>

QString convert(QString x){
    if (x.contains(",")) {
        return x.replace(x.indexOf(","), 1, ".");
    } else {
        return x;
    }
}

