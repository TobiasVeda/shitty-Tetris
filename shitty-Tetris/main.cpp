#include "Process.h"
#include <thread>
#include <mutex>

//TODO: Fix include order, put defenition of keyup,down,right in class, add const when what the function recieves shouldnt be edited
//put view in class to prevent passing?? Moved, but not sure if all includes fixed
//Deconstruct cleared blocks??
//all things relative to view will break when view is expanded to include "next blocks" and "hold".
//      can probably still use center, but must expand from center with tilesize * tilecount_x/y
// make move diagonal possible
//TODO: Error handling when not finding texture, key_hold for multiple inputs


int main(){
    std::thread p1(Process::game_loop, 0);
    p1.join();
}

