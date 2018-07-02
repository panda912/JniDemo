//
// Created by panda on 6/28/18.
//

#ifndef JNIDEMO_MYDIGEST_H
#define JNIDEMO_MYDIGEST_H

#include <string>

using namespace std;

class mydigest {
public:
    static string calcDigest(char *message, char *type);

    static string calcFileDigest(char *filePath, char *type);
};


#endif //JNIDEMO_MYDIGEST_H
