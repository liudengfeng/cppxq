#pragma once

#include "board.hpp"
#include "rule2022.hpp"

using namespace rule2022;

// =================== 辅助函数 ===========================

/// @brief 坐标是否参与到捉移动列表
/// @param c 坐标
/// @param hist 捉移动列表
/// @return 真或假【限于先手，即列表奇数位置的移动】
bool is_participated(const Coord &c, const moveVec_t &hist);

/// @brief 移动是否参与到捉移动列表
/// @param m 移动
/// @param hist 捉移动列表
/// @return 真或假【限于先手，即列表奇数位置的移动】
bool is_participated(const Move &m, const moveVec_t &hist);

/// @brief 相关吃是否为捉移动列表开头
/// @param related_eats 相关吃移动列表
/// @param hist 捉移动列表
/// @return 真或假
bool is_participated(const moveVec_t &related_eats, const moveVec_t &hist);

/// @brief 组合形成兑移动列表
/// @param m 吃移动
/// @param hist 吃后对手吃回移动列表
/// @return 移动列表，长度始终为2
moveVec_t get_dui_path(const Move &m, const moveVec_t &hist);

/// @brief 移动的棋子是否为将、帅、兵或卒
/// @param move 移动
/// @return 真或假
bool is_pk_move(const Move &move);

/// @brief 从捉历史中提出帅、兵捉
/// @param hist 捉列表
/// @return 帅、兵捉
Move get_pk_eat(const moveVec_t &hist);

/// @brief 获取兑移动列表
/// @param board 棋局
/// @param tgt 兑目标
/// @param dui 兑吃
/// @return 兑移动列表
moveVec_t get_dui_history(const Board &board, const Coord &tgt, Move dui);

// ➡️ 对手应将后player是否一定有强子可吃【兑后将军辅助分析】
// ➡️ 将军得子可能非常耗时，使用一步应将来简化
bool _has_strong_piece_to_eat(const Board &board, const Color &player);

/// @brief 获取共同攻击点
/// @param board 棋局
/// @param moved 已经执行的移动
/// @return 共同攻击坐标
// ➡️ 与已经执行的移动相关
// ➡️ 一般为车、炮、马联合捉子
// ➡️ 如果攻击数量少于2个，返回默认无效坐标{9, 9}
Coord get_common_attack(const Board &board, Move &moved);

/// @brief 棋局只有一个可自由移动的进攻子力
/// @param board 棋局
/// @param moved 已经执行的移动
/// @return 真或假
bool only_has_one_attack(const Board &board, Move &moved);

// 移动前提子可吃无根子列表
std::vector<PieceType> _eats_before_move(const Board &board);

// 根据捉路径提取捉对象键值对列表，以捉为键、被捉对象为值。
std::vector<std::pair<PieceInfo, PieceInfo>> get_zhuo_objects(const moveVec_t &hist);

// ➡️ 移动前可捉对象必须确保吃后不会被杀
moveVec_t ensure_zhuo_objects_before_moved(const Board &board, moveVec_t hist);

// 棋盘所动之子本可直接吃得子或盘面上本可将军得子的捉对象列表
// ➡️ 所动之子本可吃得子列表
// ➡️ 盘面上本可将军得子列表
moveVec_t get_zhuo_objects_before_moved(const Board &board);

// 捉路径价值是否相等
bool _is_same_dz(const moveVec_t &before, const moveVec_t &after);

// 同样的将军得子结果
bool _is_same_jjdz(const moveVec_t &hist0, const moveVec_t &hist1);

// 是否为兵、帅捉
// 26.1 帅(将)、兵(卒)本身允许长捉(见图14)
bool is_pk_zhuo(const Board &board, Move &moved, const moveVec_t &hist);

// 26.1.3 上一着将军，走动帅(将)应将直接判“闲”
// 26.1.4 走动其他子应将产生的“捉”或“杀”，如应将前不存在，按“捉”或“杀”处理；如应将前已经存在，则为“闲”
bool is_response_jj_xian(const Board &board, Move &moved, const moveVec_t &hist);

/// @brief 特殊情形下判闲
/// @param board 棋局
/// @param moved 已经执行的移动
/// @param hist 捉子移动列表
/// @return 真或假
bool is_xian(const Board &board, Move &moved, const moveVec_t &hist);

// =================== 内部函数 ===========================

/// @brief 为移动标注`闲`标记
/// @param moved 已经执行的移动
/// @param ended 结束标记
void mark_xian_flag(Move &moved, bool &ended);

/// @brief 为移动标注`兑`标记
/// @param moved 已经执行的移动
/// @param move 对手吃后、本方执行的`兑`移动
void mark_dui_flag(Move &moved, const Move &move);

/// @brief 为移动标注`杀`标记
/// @param board 执行移动后的棋局
/// @param moved 已经执行的移动
/// @param ended 结束标记
void mark_sha_flag(const Board &board, Move &moved, bool &ended);

/// @brief 为移动标注`捉`标记
/// @param board 执行移动后的棋局
/// @param moved 已经执行的移动
/// @param ended 结束标记
/// @param hist 模拟输出的捉移动列表
void mark_zhuo_flag(const Board &board, Move &moved, bool &ended, const moveVec_t &hist);

// 模拟将军得子
moveVec_t _simulate_jjdz(const Board &board, const Color &player, const Move &dui = EMPTY_MOVE);

// 模拟互吃得子
moveVec_t _simulate_cdz(const Board &board, const Color &player,
                        const Move &dui = EMPTY_MOVE,
                        const Coord &tgt = EMPTY_COORD);

// 可保护上一着被吃的棋子
bool is_can_protected_last_eated(const Board &board);

/// @brief 回退一步如执行吃移动是否会被杀
/// @param board 棋局
/// @param player 玩家
/// @param eat 尚未执行的吃
/// @return 真或假
bool is_be_killed(const Board &board, const Color &player, Move eat);

/// @brief 是否相关
/// @param board 棋局
/// @param moved 已经执行的移动
/// @param hist 捉子历史
/// @param cands 候选
/// @return 真或假
bool is_jj_related(const Board &board, Move &moved, const moveVec_t &hist, const moveVec_t &cands);

/// @brief 移动是否避吃
/// @param board 棋局
/// @param moved 已经执行的移动
/// @return 真或假
bool is_avoid_eat(const Board &board, Move &moved);

// =================== 标注函数 ===========================

// 检测断根捉吃移动
// ➡️ 如存在捉吃，返回有效移动，否则为无效移动
// ⚠️ 前提条件：不存在相关吃
Move get_cut_root_eat(const Board &board);

// 标记已经完成的移动是否为`闲`
// ➡️ 上一步将军，本次移动将、帅应将，`闲`【即使有杀或捉】
void mark_xian(const Board &board, Move &moved, bool &ended);

// 标记已经完成的移动是否为`将`
void mark_jj(const Board &board, Move &moved, bool &ended);

// 标记已经完成的移动是否为`兑`
// ➡️ 如果兑后将军，在兑的基础上进行将军得子模拟 图17-3 得子为捉 `ended`标记为`true` 结束
// ➡️ 标记为`兑`，后续继续除兑移动外的其他得子
void mark_dui(const Board &board, Move &moved, bool &ended, const Coord &c, Move dui);

// 标记已经完成的移动是否为`杀`
// ⚠️ 在标记`兑`之后
void mark_sha(const Board &board, Move &moved, bool &ended, Move dui);

// // ➡️ 捉车
// // ➡️ 相关吃存在吃车，首先进行互吃模拟
// // ⚠️ 限定为相关吃
// void mark_zhuo_rook(const Board &board, Move &moved, bool &ended, moveVec_t related, Move dui);

// ➡️ 所动之子捉无根保护的强子【所动之子非将、兵】
// ➡️ 吃后非将军【如为将则需要进行将军得子模拟】、不会立即输棋、吃后不会导致为对手产生相关吃
// ⚠️ 限定为相关吃
// ⚠️ 如图8-1 红车捉卒，出于性能考虑，没有对每一步吃后做杀模拟，黑车亦可吃红兵，表面上无法得子
void mark_zhuo_no_root(const Board &board, Move &moved, bool &ended, Move eat);

// 断根捉子
// ➡️ 可吃无根子
// ➡️ 模拟：如果回退一步，继续吃目标棋子，会被对方吃回
// ⚠️ 除相关吃外的其他吃
// ⚠️ 断根捉子后完成标注，不再进行`调整闲`
void mark_zhuo_cut_root(Board &board, Move &moved, bool &ended, moveVec_t related);

// ➡️ 避吃捉
// ➡️ 走子方移动后无相关吃
// ➡️ 走子方移动的目的是避开对方吃
// ➡️ 走子方移动后可得子
// ⚠️ 不需要检查有效性
// ⚠️ 除相关吃外的其他吃
// 图12-2
void _zhuo_avoid_eated(const Board &board, Move &moved, bool &ended, moveVec_t related);

// ➡️ 避杀捉
// ➡️ 要么非帅、兵移动，要么帅、兵移动，且相关吃为空
// ➡️ 回退一步，捉原本就存在
// ➡️ 捉不在相关吃列表中，而是其他可吃的移动
// ➡️ 只是一旦吃后会被杀，必须先避杀后才能吃
// ➡️ 模拟：如回退一步，继续吃得子目标，则会导致被杀
// ⚠️ 除相关吃外的其他吃
// 图08-2 参考图20-4
void mark_zhuo_avoid_killed(const Board &board, Move &moved, bool &ended, const moveVec_t &related);

/// @brief 标记互吃得子。如存在共同攻击目标，以吃目标为候选，否则限定于相关吃。⚠️ 限定相关吃，不需要进行无关性检查
/// @param board 棋局
/// @param moved 已经执行的移动
/// @param ended 结束标记
/// @param dui_eat 兑吃
/// @param related_eats 相关吃列表
void mark_zhuo_related_chi(const Board &board, Move &moved, bool &ended, const Move &dui_eat, const moveVec_t &related_eats);

/// @brief 标记互吃得子，以除已经检查过的相关吃外，其余有效吃为基础
/// @param board 棋局
/// @param moved 已经执行的移动
/// @param ended 结束标记
/// @param dui_eat 兑吃
/// @param related_eats 相关吃列表
// ➡️ 参考图图34-3 移动上一着被捉对象，证明相关
void mark_zhuo_not_related_chi(const Board &board, Move &moved, bool &ended, const Move &dui_eat, const moveVec_t &related_eats);

// 标记将军得子
// ➡️ 模拟将军得子
// ➡️ 存在得子路径时，需要检验
// 1. 如非抽将得子时，所动之子没有参与捉子，不可判捉
// 2. 模拟：回退一步，如将军得子本质没有发生变化，不可判捉
// 3. 如此前判闲，维持原判，结束模拟
void mark_zhuo_jjdz(const Board &board, Move &moved, bool &ended, const Move &dui, const moveVec_t &related, const moveVec_t &cands);

// 吃后将军得子
// ➡️ 此前没有标记为将军、杀、捉
// ➡️ 相关吃逐个吃，对手吃回、模拟将军得子
// ➡️ 无论对手采用哪种方式吃回都可将军得子，则标记为捉
// ⚠️ 完成正常互吃、将军得子后进行 参考图34
void mark_zhuo_chi_jjdz(const Board &board, Move &moved, bool &ended, moveVec_t related, Move dui);

/// @brief 是否应当首先进行将军得子模拟
/// @param board 棋局
/// @param moved 已经执行的移动
/// @param cands 候选移动
/// @param related 相关吃
/// @param dui 兑移动
/// @return 真或假。
// 以下情形应先执行将军得子模拟
// ➡️ 不存在相关吃且不存在共同攻击目标 图02-3
// ➡️ 相关吃中存在吃同时将军时 图03-2
// ➡️ 移动候选中存在非吃移动，走后其他子将军 图09-2
bool is_jj_first(const Board &board, Move &moved, const moveVec_t &cands, const moveVec_t &related, Move dui);

/// @brief 找出棋局中吃不得离线的目标
/// @param board 棋局
/// @param cands 有效候选移动
/// @return 移动。如不存在，返回空移动
Move get_can_not_offline_eat(const Board &board, const moveVec_t &cands);

/// @brief 获取相关吃中吃无根子。⚠️ 如移动帅、兵后，非帅、兵所捉无根子与帅、兵捉无根子等价，优先非帅、兵捉 参考图20-1
/// @param board 棋局
/// @param cands 有效候选移动
/// @param related 相关吃
/// @param dui 兑吃
/// @return 吃无根子移动
Move get_noroot_eat(const Board &board, const moveVec_t &cands, moveVec_t related, const Move &dui);

// 标记捉
// ➡️ 1. 捉车：无论车是否有根保护，返回捉，且无需再检查。例外：兵捉车为闲
// ➡️ 2. 断根捉
// ➡️ 3. 模拟互吃得子
// ➡️ 避吃捉
// ➡️ 避杀捉
// ➡️ 将军得子
// ⚠️ 位于标记`兑`之后
void mark_zhuo(const Board &board, Move &moved, bool &ended, moveVec_t related, Move dui);

// 标记移动类型
// ➡️ 标记闲
// ➡️ 标记将
// ➡️ 标记兑
// ➡️ 标记杀
// ➡️ 标记捉
// ➡️ 调整闲
void mark_move(Board &board, Move &move);

// =================== 判定函数 ===========================

// 生成序列长度为n的组合序号列表对
std::vector<std::vector<size_t>> get_combination_idx(size_t n);

// 24.13 禁止着法：
// 凡单方面走出长将、长杀、长捉、一将一杀、一将一捉、一杀一捉等循环重复的攻击性着法，统称为“禁止著法”(见图8、参考图10)
bool is_prohibit_group(const Move &one, const Move &two);

bool is_prohibit_group(const moveVec_t &moves);

// 是否为在三个或三个以上点上，连续以禁止着法达九个回合的着法
bool is_r9moves(const moveVec_t &moves);

// 组合移动是否应该变着
bool should_change(const Move &one, const Move &two);

bool should_change(const moveVec_t &moves);

moveVec_t get_gamer_history(const moveVec_t &moves, bool first);

/// @brief 判例裁决
/// @param moves 已经标注过的移动历史
/// @return 当出现重复局面时裁决结果
Result adjudicate(const moveVec_t &moves);

Result adjudicate(const moveVec_t &moves, Color starter);

class XqBoard : public Board
{
private:
    bool _mark_flag = true;

public:
    /// @brief 克隆棋盘
    /// @return 棋盘
    XqBoard clone() const;

    /// @brief 设置是否进行移动类型标注
    void set_use_rule_flag(bool flag) { _mark_flag = flag; };

    /// @brief 是否需要继续标注
    /// @return 真或假
    bool is_continue_mark();

    /// @brief 当步数超过18步时，对移动类型进行标注
    // 先行、后行任一方9着含`闲`即可退出，减少标注量
    void on_over_18_steps();

    // 三次重复为小概率事件，而标记移动非常耗时，使用事件触发
    void on_repeat(size_t t, size_t times) override final;

    void step(Move &move);

    void step(const int move_id);

    void step(int x1, int y1, int x2, int y2);

    void step(const std::string move_str);
};