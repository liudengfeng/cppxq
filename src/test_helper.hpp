#pragma once

#include <string>
#include <vector>

#include "board.hpp"

// 上下左右翻转fen
std::string fliped_fen(std::string fen)
{
    Board board;
    board.set_pieces(fen);
    auto b2 = board.flipup();
    return b2.get_fen_string();
}

std::vector<std::string> fliped_moves(std::vector<std::string> moves)
{
    std::vector<std::string> ret;
    for (auto &s : moves)
    {
        auto m = make_move(s);
        ret.push_back(m.UDLR().toString());
    }
    return ret;
}
