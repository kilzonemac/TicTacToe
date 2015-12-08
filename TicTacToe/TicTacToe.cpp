#include "TicTacToe.h"
#include <cstdio>
#include <iterator>

int TicTacToe::leaf_counter = 0;

bool TicTacToe::is_win() const {
    const int pt = parent->turn;
    switch (move) {
    case 0:
        return s[1] == pt && s[2] == pt ||
               s[3] == pt && s[6] == pt ||
               s[4] == pt && s[8] == pt;
    case 1:
        return s[0] == pt && s[2] == pt ||
               s[4] == pt && s[7] == pt;
    case 2:
        return s[1] == pt && s[0] == pt ||
               s[5] == pt && s[8] == pt ||
               s[4] == pt && s[6] == pt;
    case 3:
        return s[4] == pt && s[5] == pt ||
               s[0] == pt && s[6] == pt;
    case 4:
        return s[3] == pt && s[5] == pt ||
               s[1] == pt && s[7] == pt ||
               s[0] == pt && s[8] == pt ||
               s[2] == pt && s[6] == pt;
    case 5:
        return s[4] == pt && s[3] == pt ||
               s[2] == pt && s[8] == pt;
    case 6:
        return s[7] == pt && s[8] == pt ||
               s[3] == pt && s[0] == pt ||
               s[4] == pt && s[2] == pt;
    case 7:
        return s[6] == pt && s[8] == pt ||
               s[4] == pt && s[1] == pt;
    case 8:
        return s[7] == pt && s[6] == pt ||
               s[5] == pt && s[2] == pt ||
               s[4] == pt && s[0] == pt;
    default:
        return false;
    }
}

TicTacToe::TicTacToe():
    turn(MAX), move(-1), depth(1), s(), parent(nullptr) {
    search();
}

TicTacToe::TicTacToe(const TicTacToe *parent, int move):
    turn(parent->turn == MAX ? MIN : MAX), move(move), depth(parent->depth + 1), parent(parent) {
    std::copy(std::begin(parent->s), std::end(parent->s), s);
    s[move] = parent->turn;
    bool iswin = is_win();
    if (iswin || depth == N_POS) {
        // This is a leaf node.
        ++leaf_counter;
    } else
        search();
}

void TicTacToe::search() {
    for (int p = 0; p < N_POS; ++p) {
        if (s[p] == ZERO) {
            // ReSharper disable once CppNonReclaimedResourceAcquisition
            children[p] = new TicTacToe(this, p);
        }
    }
}

TicTacToe::~TicTacToe() {
    for (TicTacToe *child : children)
        if (child) delete child;
}

// Visualize a stone
char v(int s) {
    const char X = 'x', O = 'o', S = ' ';
    if (s == TicTacToe::MAX)
        return X;
    else if (s == TicTacToe::MIN)
        return O;
    else // if (s == TicTacToe::ZERO)
        return S;
}

std::ostream &operator<<(std::ostream &out, const TicTacToe &t) {
    const int BUFSIZE = 256;
    char buffer[BUFSIZE];
    snprintf(
        buffer, BUFSIZE,
        "+---+---+---+\n"
        "| %c | %c | %c |\n"
        "+---+---+---+\n"
        "| %c | %c | %c |\n"
        "+---+---+---+\n"
        "| %c | %c | %c |\n"
        "+---+---+---+\n",
        v(t.s[0]), v(t.s[1]), v(t.s[2]),
        v(t.s[3]), v(t.s[4]), v(t.s[5]),
        v(t.s[6]), v(t.s[7]), v(t.s[8])
    );
    return out << buffer;
}