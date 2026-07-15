#include "scenes.h"


int main(){
    scene s = make_book1_final(400, 100);
    s.cam.render(s.world);
    return 0;
}