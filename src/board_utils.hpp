#pragma once

#include "board.hpp"

// 中国象棋比赛规则2022版本
namespace rule2022
{
    // 车、马、炮为强子
    bool is_strong_piece(PieceType t);

    // 对先手而言，移动列表与候选移动组合后是否为有效的将军得子模拟序列
    bool is_jdz_sequence(const moveVec_t &hist, const Move &cand);

    // 走子前后相关吃列表
    // ➡️ 只比较一步移动前后的盘面
    // ➡️ 凡是新增部分，都列入相关吃列表
    // 提子为车
    // ➡️ 移动后，其他棋子与车捉同一对象的移动列入相关吃列表 参考图 36-4 黑马捉象
    // ➡️ 移动后，其他子吃子后依然在车火力支援范围内也列入相关吃列表
    // 提子为炮
    // ➡️ 移动后，其他棋子与炮捉同一对象的移动列入相关吃列表 参考图 25-3 红车捉炮
    // ➡️ 移动后，其他子吃子后依然在炮火力支援范围内也列入相关吃列表 图27-2 黑车捉马
    // 针对对手
    // ➡️ 走子方移动后减少对棋子的保护，对手吃该子列入相关吃列表
    moveVec_t related_eat_after_moved(const Board &board, bool for_next_player = false);

    // ➡️ 将军、应将后相对`next player`的新增吃，即将军方将军、对手应将产生的吃
    moveVec_t related_eat_after_check(const Board &board);

    // ➡️ 新增吃
    moveVec_t new_added_eats(const moveVec_t &news, const moveVec_t &olds);

    // // ➡️ 将军、应将、吃子后，返回可吃将军棋子的移动候选
    // // ➡️ 第一步将
    // // ➡️ 第三步吃
    // // ➡️ 相对`next player`可吃将军棋子的移动列表
    // moveVec_t eat_checked_cands(const Board &board);

    // ➡️ 找出双方可互换开始、结束坐标的互吃
    // ➡️ 棋子价值相等
    // 注意：相对于 next player 而言的移动
    Move get_dui_move(const Board &board);

    // 棋盘兑子坐标
    // ➡️ 找出双方可互换开始、结束坐标的互吃移动
    // ➡️ 需要证明兑移动与最后一步相关
    // ➡️➡️ 兑移动此前不存在，走子后才产生，图02-2 参考图04-4
    // ➡️➡️ 最后一步可吃兑开始坐标的棋子，图30-2
    // ➡️➡️ 如兑移动执行完成，最后一步可吃兑结束坐标的棋子，图30-3
    Coord get_dui_coord(const Board &board);

    // 排序将军候选移动【优先抽将吃】
    void sorted_jj_cands(const Board &board, const Color &player, moveVec_t &jjs);
}