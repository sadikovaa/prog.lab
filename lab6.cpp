#include <iostream>

class rubics_cube{
private:
    unsigned short int  front_side[3][3];
    unsigned short int  right_side[3][3];
    unsigned short int  back_side[3][3];
    unsigned short int  left_side[3][3];
    unsigned short int  up_side[3][3];
    unsigned short int  down_side[3][3];

    void layer_copy(unsigned short int (&l1)[3], unsigned short int (&l2)[3]){
        for (int i=0; i<3; i++)
            l1[i] = l2[i];
    }
    void side_copy(unsigned short int (&s1)[3][3], unsigned short int (&s2)[3][3]){
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                s1[i][j] = s2[i][j];
    }
    void clockwise_side_turn(unsigned short int (&s)[3][3]){
        unsigned short int new_s[3][3];
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                new_s[2-i][j] = s[i][j];
        side_copy(s, new_s);
    }
    void counterclockwise_side_turn(unsigned short int (&s)[3][3]){
        unsigned short int new_s[3][3];
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                new_s[j][2-i] = s[i][j];
        side_copy(s, new_s);
    }
    void left_layer_turn(unsigned short int n){
        unsigned short int layer[3];
        layer_copy(layer, back_side[n]);
        layer_copy(back_side[n], left_side[n]);
        layer_copy(left_side[n], front_side[n]);
        layer_copy(front_side[n], right_side[n]);
        layer_copy(right_side[n], layer);
    }
    void right_layer_turn(unsigned short int n){
        unsigned short int layer[3];
        layer_copy(layer, back_side[n]);
        layer_copy(back_side[n], right_side[n]);
        layer_copy(right_side[n], front_side[n]);
        layer_copy(front_side[n], left_side[n]);
        layer_copy(left_side[n], layer);
    }
    void left_turn_first(){
        left_layer_turn(1);
        clockwise_side_turn(up_side);
    }
    void left_turn_second(){
        left_layer_turn(1);
    }
    void left_turn_third(){
        left_layer_turn(1);
        clockwise_side_turn(down_side);
    }
    void right_turn_first(){
        right_layer_turn(1);
        counterclockwise_side_turn(up_side);
    }
    void right_turn_second(){
        right_layer_turn(1);
    }
    void right_turn_third(){
        right_layer_turn(1);
        counterclockwise_side_turn(down_side);
    }
    void up_turn_first(){
    }
    void up_turn_second(){
    }
    void up_turn_third(){
    }
    void down_turn_first(){
    }
    void down_turn_second(){
    }
    void down_turn_third(){
    }
    void clockwise_turn_first(){
    }
    void clockwise_turn_second(){
    }
    void clockwise_turn_third(){
    }
    void counterclockwise_turn_first(){
    }
    void counterclockwise_turn_second(){
    }
    void counterclockwise_turn_third(){
    }
private:

};

int main() {
    return 0;
}
