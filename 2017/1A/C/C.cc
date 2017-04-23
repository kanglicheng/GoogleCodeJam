#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>
#include <set>

using namespace std;

long long dragon_health, dragon_attack;
long long knight_health, knight_attack;
long long buff, debuff;

const long long INF = 1000000000000LL;

long long ceil_div(long long a, long long b) {
    return (a + (b - 1)) / b;
}

long long find_buff_attack_turns() {
    long long turns = 0;
    long long opt = ceil_div(knight_health, dragon_attack);
    while (1) {
        ++ turns;
        long long cur = turns + ceil_div(knight_health, dragon_attack + turns * buff);
        if (cur < opt) {
            opt = cur;
        }
        else if (cur > opt) return opt;
    }
}

long long find_buff_turns(long long dragon_remain_health, long long knight_attack, long long second_stage) {
    if (knight_attack == 0) return second_stage;
    long long at_most_turns = ceil_div(dragon_remain_health, knight_attack);
    if (second_stage <= at_most_turns) return second_stage;

    long long ret = at_most_turns;
    second_stage -= at_most_turns - 1;

    dragon_remain_health = dragon_health - knight_attack;
    if (dragon_remain_health <= 0) return INF;

    at_most_turns = ceil_div(dragon_remain_health, knight_attack);
    if (at_most_turns == 1) {
        if (second_stage == 1) return ret + 1;
        return INF;
    }
    ret += second_stage + ceil_div(second_stage - at_most_turns, at_most_turns - 1);
    return ret;
}

long long solve() {
    long long second_stage = find_buff_attack_turns();
    //cout << "second stage = " << second_stage << endl;
    long long opt = INF;
    long long debuff_turns = 0;
    long long last = -1;
    long long dragon_remain_health = dragon_health;
    while (1) {
        if (knight_attack == 0 || dragon_health / knight_attack != last) {
            long long buff_turns = find_buff_turns(dragon_remain_health, knight_attack, second_stage);
            //cout << dragon_remain_health << " " << knight_attack << " " << second_stage << endl;
            //cout << "buff_turns = " << buff_turns << endl;
            //cout << "buff turns = " << buff_turns << endl;
            opt = min(opt, debuff_turns + buff_turns);
            if (knight_attack > 0)
                last = dragon_health / knight_attack;
        }
        if (knight_attack == 0 || debuff == 0) return opt;

        if (dragon_remain_health <= knight_attack - debuff) {
            dragon_remain_health = dragon_health - knight_attack;
            ++ debuff_turns;
        }
        knight_attack = max(knight_attack - debuff, 0LL);
        dragon_remain_health -= knight_attack;
        ++ debuff_turns;
        if (dragon_remain_health <= 0) return opt;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        cin >> dragon_health >> dragon_attack >> knight_health >> knight_attack >> buff >> debuff;
        printf("Case #%d: ", test);
        long long turns = solve();
        if (turns == INF)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << turns << endl;
    }
    return 0;
}
