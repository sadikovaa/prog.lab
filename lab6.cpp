#include <iostream>
class rubics_cube{
private:
    unsigned short int  front_side[3][3]{};
    unsigned short int  right_side[3][3]{};
    unsigned short int  back_side[3][3]{};
    unsigned short int  left_side[3][3]{};
    unsigned short int  up_side[3][3]{};
    unsigned short int  down_side[3][3]{};

public:
    static void coloring(unsigned short int (&l1)[3][3], unsigned short int color){
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                l1[i][j] = color;
    }
    explicit rubics_cube(){
        coloring(front_side, 0);
        coloring(right_side, 1);
        coloring(back_side,2);
        coloring(left_side, 3);
        coloring(up_side, 4);
        coloring(down_side, 5);
    }

private:
    static void layer_copy(unsigned short int (&l1)[3][3], unsigned short int (&l2)[3][3],unsigned short int n){
        for (int i=0; i<3; i++)
            l1[n][i] = l2[n][i];
    }
    static void column_copy(unsigned short int (&l1)[3][3], unsigned short int (&l2)[3][3], unsigned short n){
        for (int i=0; i<3; i++)
            l1[i][n] = l2[i][n];
    }
    static void column_and_layer(unsigned short int (&l)[3][3], unsigned short int (&c)[3][3], unsigned short n){
        for (int i=0; i<3; i++)// если поворачиваешь по часовой стрелке то стоблец в строчку, если против строчка в столбец
            l[n][i] =c[2-i][n];
    }
    static void layer_and_column(unsigned short int (&l)[3][3], unsigned short int (&c)[3][3], unsigned short n){
        for (int i=0; i<3; i++) //зеркально прошлому
            l[n][i] =c[i][n];
    }
    static void side_copy(unsigned short int (&s1)[3][3], unsigned short int (&s2)[3][3]){
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                s1[i][j] = s2[i][j];
    }
    void clockwise_side_turn(unsigned short int (&s)[3][3]){
        unsigned short int new_s[3][3];
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                new_s[j][2-i] = s[i][j];
        side_copy(s, new_s);
    }
    void counterclockwise_side_turn(unsigned short int (&s)[3][3]){
        unsigned short int new_s[3][3];
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                new_s[2-j][i] = s[i][j];
        side_copy(s, new_s);
    }
    void left_horiz_layer_turn(unsigned short int n){
        unsigned short int layer[3][3];
        layer_copy(layer, back_side, n);
        layer_copy(back_side, left_side, n);
        layer_copy(left_side, front_side, n);
        layer_copy(front_side, right_side, n);
        layer_copy(right_side, layer, n);
    }
    void right_horiz_layer_turn(unsigned short int n){
        unsigned short int layer[3][3];
        layer_copy(layer, back_side, n);
        layer_copy(back_side, right_side, n);
        layer_copy(right_side, front_side, n);
        layer_copy(front_side, left_side, n);
        layer_copy(left_side, layer, n);
    }
    void up_vertical_column_turn(unsigned short int n){
        unsigned short int layer[3][3];
        column_copy(layer, up_side, n);
        column_copy(up_side, front_side, n);
        column_copy(front_side, down_side, n);
        column_copy(down_side, back_side, n);
        column_copy(back_side, layer, n);
    }
    void down_vertical_column_turn(unsigned short int n){
        unsigned short int column[3][3];
        column_copy(column, front_side, n);
        column_copy(front_side, up_side, n);
        column_copy(up_side, back_side, n);
        column_copy(back_side, down_side, n);
        column_copy(down_side, column, n);
    }
    void clockwise_column_side_turn(unsigned short int n){
        unsigned short int column[3][3];
        column_copy(column, right_side, n);
        layer_and_column(right_side, down_side, n);
        column_and_layer(down_side, left_side, n);
        layer_and_column(left_side, up_side, n);
        column_and_layer(up_side, column, n);
    }
    void counterclockwise_column_side_turn(unsigned short int n){
        unsigned short int column[3][3];
        column_copy(column, right_side, n);
        layer_and_column(right_side, up_side, n);
        column_and_layer(up_side, left_side, n);
        layer_and_column(left_side, down_side, n);
        column_and_layer(down_side, column, n);
    }

public:
    void left_turn_first(){
        left_horiz_layer_turn(0);
        clockwise_side_turn(up_side);
    }
    void left_turn_second(){
        left_horiz_layer_turn(1);
    }
    void left_turn_third(){
        left_horiz_layer_turn(2);
        clockwise_side_turn(down_side);
    }
    void right_turn_first(){
        right_horiz_layer_turn(0);
        counterclockwise_side_turn(up_side);
    }
    void right_turn_second(){
        right_horiz_layer_turn(1);
    }
    void right_turn_third(){
        right_horiz_layer_turn(2);
        counterclockwise_side_turn(down_side);
    }
    void up_turn_first(){
        counterclockwise_side_turn(left_side);
        up_vertical_column_turn(0);
    }
    void up_turn_second(){
        up_vertical_column_turn(1);
    }
    void up_turn_third(){
        counterclockwise_side_turn(right_side);
        up_vertical_column_turn(2);
    }
    void down_turn_first(){
        clockwise_side_turn(left_side);
        down_vertical_column_turn(0);
    }
    void down_turn_second(){
        down_vertical_column_turn(1);
    }
    void down_turn_third(){
        clockwise_side_turn(right_side);
        down_vertical_column_turn(2);
    }
    void clockwise_turn_first(){
        clockwise_side_turn(front_side);
        clockwise_column_side_turn(0);
    }
    void clockwise_turn_second(){
        clockwise_column_side_turn(1);
    }
    void clockwise_turn_third(){
        clockwise_side_turn(back_side);
        clockwise_column_side_turn(2);
    }
    void counterclockwise_turn_first(){
        counterclockwise_side_turn(front_side);
        counterclockwise_column_side_turn(0);
    }
    void counterclockwise_turn_second(){
        counterclockwise_column_side_turn(1);
    }
    void counterclockwise_turn_third(){
        counterclockwise_side_turn(back_side);
        counterclockwise_column_side_turn(2);
    }

};

int main() {
    return 0;
}
