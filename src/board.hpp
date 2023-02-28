#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <random>
#include <list>

#include "common.hpp"
#include "utils.hpp"
#include "move_maps.hpp"
#include "hash_num.hpp"

using moveVec_t = std::vector<Move>;
using hashVec_t = std::vector<uint64_t>;

using infoVec_t = std::vector<PieceInfo>;
using coordVec_t = std::vector<Coord>;

enum class B_FinishReason
{
    FR_NO_RESULT = 0,
    // 分出胜负
    FR_END,
    // 无子力进攻
    FR_NO_POWER,
    // 连续60回合未吃子
    FR_MAX_NO_EAT,
    // 三次重复
    FR_MAX_REPEATION,
    // 未应将
    FR_NO_REPLY,
    // 将、帅照面
    FR_FF,
    // 将、帅被吃
    FR_EATED,
    // 不合法走子
    FR_ILLEGAL
};

template <class T>
constexpr bool contains(std::vector<T> const &v, T const &x)
{
    return !(v.empty() ||
             std::find(v.begin(), v.end(), x) == v.end());
}

template <class T>
constexpr bool contains(std::set<T> const &v, T const &x)
{
    return !(v.empty() ||
             std::find(v.begin(), v.end(), x) == v.end());
}

static const char *FR_ENUM_STR[] = {"比赛进行中", "比赛已结束", "无力进攻和", "未吃子判和", "三次重复负", "未应将判负", "不合法走子"};

// 枚举值转换为字符串
inline std::string getStringForEnum(const B_FinishReason enum_val)
{
    std::string enum_str(FR_ENUM_STR[static_cast<size_t>(enum_val)]);
    return enum_str;
}

/// @brief 将映射序号转换为代表移动的4位数字符串
/// @param action 映射序号
/// @return 代表移动的4位数字符串
std::string action2str(int action);

/// @brief 移动字符串转换为其映射序号
/// @param movestr 4位数字符串
/// @return 整数序号
int str2action(const std::string movestr);

/// @brief 移动左右互换
/// @param movestr 4位整数字符串代表的移动
/// @return 4位整数字符串
std::string move2lr(const std::string movestr);

/// @brief 棋子英文字符名称
/// @param p 棋子类型
/// @param c 棋子颜色
/// @return 字符串
std::string getSymbol(const PieceType p, const Color c);

/// @brief 棋子中文名称
/// @param p 棋子类型
/// @param c 棋子颜色
/// @return 中文字符串
std::string getCNSymbol(const PieceType p, const Color c);

// 计算二个坐标之间的x轴与y轴偏移值
std::pair<int, int> deltaXY(const Coord c1, const Coord c2);

/// @brief 中文名称
/// @param player 走子方
/// @return 中文字符串
std::string color_cn_name(const Color &player);

// 是否为过河兵卒
bool is_cross_river_pawn(const PieceInfo &p);

// 是否为刚过河位置的兵、卒
bool is_just_cross_river_pawn(const PieceInfo &p);

// 二个坐标点在同一条直线
bool is_in_same_line(const Coord &c1, const Coord &c2);

// 棋子价值
int get_piece_value(const PieceInfo &p);

// 简化版本输出python
struct Piece
{
    int x;
    int y;
    int color_id;
    int piece_id;
    std::string color_name;
    std::string piece_name;
};

/// @brief
class Board
{
protected:
    // 棋盘棋子信息
    infoVec_t _infos;

    // 当前hash值
    uint64_t _hash = INIT_HASH;

    // hash 历史
    hashVec_t _hash_keys;

    // 结束原因
    B_FinishReason _reason;

    std::string _s_reason;

    moveVec_t _moves_history;

    Color _first_player = S_RED;
    // Next player.
    Color _next_player = S_RED;

    // 步数 从1开始
    size_t _ply = 1;

    // 连续未吃子步数
    // 在连续N个回合中，双方都没有吃过一个棋子
    size_t _no_eat;

    // 棋局最终结果
    Result _result;

    // 初始化默认棋盘
    void init_board();

    // 走子【内部函数】
    void _do_move(const Move &move);

    void _simple_move(Move &move);

    // 回退指定移动
    void undo_simple_move(const Move &move);

    // 当棋盘设置或运行错误时触发
    void on_board_error(const std::string msg);

    // 查找当前棋局走子方所有棋子及位置
    infoVec_t find_PCs(const Color &player) const;

    // 添加`帅`所有候选移动位置
    void add_red_king_moves(const Coord &c, moveVec_t &moves) const;

    // 添加`将`所有候选移动位置
    void add_black_king_moves(const Coord &c, moveVec_t &moves) const;

    // 添加红`士`所有候选移动位置
    void add_red_guard_moves(const Coord &c, moveVec_t &moves) const;

    // 添加黑`士`所有候选移动位置
    void add_black_guard_moves(const Coord &c, moveVec_t &moves) const;

    // 红象
    void add_red_elephant_moves(const Coord &c, moveVec_t &moves) const;

    // 黑象
    void add_black_elephant_moves(const Coord &c, moveVec_t &moves) const;

    // 红马、黑马
    void add_horse_moves(const Coord &c, moveVec_t &moves) const;

    // 红炮、黑炮
    void add_cannon_moves(const Coord &c, moveVec_t &moves) const;

    // 红车、黑车
    void add_rook_moves(const Coord &c, moveVec_t &moves) const;

    // 红兵
    void add_red_pawn_moves(const Coord &c, moveVec_t &moves) const;

    // 黑卒
    void add_black_pawn_moves(const Coord &c, moveVec_t &moves) const;

    // 添加候选移动方法工厂
    void add_cand_factory(const PieceInfo &p, moveVec_t &moves) const;

    // 生成符合棋子走子规范的候选，不判断走后
    moveVec_t _Candidates(const Color &player) const;

    // 生成尚未执行的移动其`将军`信息，即如移动后是否会导致将军，哪些子可吃到将或帅
    void _gen_jj_info(const Color &player, Move &before_move, Coord king_coord) const;

    // 对已经执行的移动，标记其将军信息
    void _gen_jj_info(const Color &player, Move &moved) const;

    // 设置连续未走子数量
    void _set_no_eat_num(int t);

    // 设置步数
    void _set_steps(int t);

    // 游戏结果
    void _ruling();

public:
    Board();

    // ********* 棋盘设置 *********

    // 清空棋子
    void clear();

    // 设置走子方
    void SetPlayer(std::string str);

    /// @brief 设置棋局结果理由
    /// @param r 整数代表 1 红胜 0 和棋 -1 红负
    /// @param reason 分出胜负理由，默认非法走子
    void SetResult(int r, const std::string reason = "非法走子");

    // 设置走子方
    void SetPlayer(Color player);

    // 清空指定位置的棋子
    void ClearPiece(Coord c);

    // 指定坐标位置放置棋子
    void set_pieces(Coord c, Color s, PieceType p, bool h = true);

    /// @brief 使用fen字符串放置棋子
    /// @param str fen字符串
    /// @param verify 是否需要验证棋子位置和数量
    /// @param include_no_eat 是否包含连续未吃子数量[-分隔的倒数第二项]
    void set_pieces(std::string str, bool verify = true, bool include_no_eat = false);

    // 使用字符放置棋子
    void set_pieces(char p, const Coord coord, bool h = true);

    // 重置棋盘
    void reset();

    // 清除移动历史列表
    void clear_history();

    // ********* 转换部分 *********

    /// @brief 棋子红黑互换
    /// @return 互换后的棋盘
    Board flipup() const;

    /// @brief 棋子位置左右互换
    /// @return 互换后的棋盘
    Board fliplr() const;

    // ********* 规则部分 *********

    // 未过河的兵或卒
    bool NotCrossRiverPawn(const Coord &c) const;

    // 过河的兵或卒
    bool IsCrossRiverPawn(const Coord &c) const;

    // 判断源坐标是否可以保护目标坐标
    bool HasRootProtected(const Coord &src, const Coord &tgt) const;

    // 判断棋子是否受到攻击
    bool BeingAttacked(const Coord &c) const;

    // 此位置的棋子被牵制【既受到保护又受到攻击】
    bool IsPinned(const Coord &c) const;

    // ********* 棋盘状态 *********

    // 棋盘上含有该棋子【坐标、颜色、棋子类型均一致】
    bool HasPiece(const PieceInfo &p) const;

    // 判断棋子是否有根保护
    // 判断即将要吃目标棋子是否有根保护
    // 【被吃子以吃子作为炮架，需要吃后才判断】
    // 如72坐标的红炮
    // 9 ＋＋象士将士象＋＋
    // 8 ＋＋＋＋＋＋＋＋＋
    // 7 ＋＋馬＋砲＋＋＋砲
    // 6 卒炮卒＋傌＋＋＋卒
    // 5 ＋＋＋＋＋＋＋馬＋
    // 4 ＋＋兵＋＋＋＋＋＋
    // 3 兵＋＋＋兵＋兵＋兵
    // 2 ＋＋＋＋炮車傌＋＋
    // 1 ＋＋＋＋＋＋＋＋＋
    // 0 ＋俥相仕帅仕相＋＋
    // ０１２３４５６７８
    bool HasRootProtected(const Coord &c) const;

    // 形式上是根，实际根本不能离线反吃，否则反吃的第一步即形成“自杀”，则称为“假根”
    bool IsFakeRootProtected(const Coord &c) const;

    // 保护指定坐标的根子其坐标列表
    coordVec_t RootProtectedCoords(const Coord &c) const;

    // 尚未执行的吃，所吃之子是否受到根保护
    bool HasRootProtected(const Move &eat) const;

    // ********* 查询部分 *********

    // 坐标受到对方攻击的数量
    // 排除自杀
    size_t NumberOfAttacked(const Coord &c) const;

    // 坐标受到本方保护的数量
    // 排除自杀
    size_t NumberOfProtected(const Coord &c) const;

    /// @brief 局面重复长度
    /// @return 重复长度
    // 如果不重复返回`0`
    size_t repetition_size() const;

    // 是否以`t`为周期重复`times`次
    bool is_multi_repetitive(size_t t, size_t times = 3) const;

    // 棋局是否结束
    // 1. 上一着对手将军，本方走后对手依旧处于将军状态
    // 2. 走子方的将、帅被吃掉
    // 3. 结果标识为结束
    bool is_game_ended() const;

    // 棋局最终结果 如2代表未结束
    int final_result() const;

    inline std::string FinishReason() const { return _s_reason; };

    // 步数
    inline size_t steps() const { return _ply; };

    // ********* 辅助分析 *********

    /// @brief 克隆棋盘
    /// @return 棋盘
    Board clone() const;

    // 验证棋子位置、数量是否合理
    void verifyBoard();

    // 连续未吃子步数
    size_t no_eat() const { return _no_eat; };

    // 下一步走子方
    Color next_player() const { return _next_player; };

    int int_next_player() const { return _next_player == S_RED ? 1 : 2; };

    uint64_t hash() const { return _hash; };

    hashVec_t keys() const { return _hash_keys; };

    // 棋子列表
    infoVec_t pieces() const { return _infos; };

    // ********* 操作部分 *********

    bool operator==(const Board &other) const
    {
        for (size_t i = 0; i < NUM_INTERSECTION; i++)
        {
            if ((this->pieces()[i].color != other.pieces()[i].color) || (this->pieces()[i].piece != other.pieces()[i].piece))
                return false;
        }
        return true;
    };

    bool operator<(const Board &other) const
    {
        if (*this == other)
        {
            return false;
        }
        return this->hash() < other.hash();
    };

    // 重点函数

    // 获取移动历史
    moveVec_t GetMoveHistory() const;

    // 最后N步的移动历史
    // 1. 如果N=0，返回空表
    // 2. 返回的移动历史先后顺序保持不变
    moveVec_t get_last_moves(size_t n) const;

    void MarkLastMove(const Move &m);

    void mark_moved_type(const Move &m, size_t i);

    // 最后一步移动
    Move get_last_move() const;

    // 上一步移动 【倒退二步】
    Move get_previous_move() const;

    std::string board_view_string(const bool viewDetail = false, const std::string &title = "比赛") const;

    /// @brief 显示棋盘
    /// @param viewDetail 是否先手细节如显示步数、走子方
    /// @param title 标题，默认标题`比赛`
    void show_board(const bool viewDetail = false, const std::string &title = "比赛") const;

    // 游戏结果字符串
    std::string game_result_string() const;

    // 下一步走子方中文字符串
    std::string next_player_string() const;

    // 棋盘string表达
    std::string board_string(const bool viewDetail = false) const;

    // 指定坐标位置棋子对象
    Piece get_piece(int x, int y) const;

    // 棋子中文名称列表
    std::vector<std::vector<std::string>> piece_cn_names() const;

    // 棋子中文颜色列表
    std::vector<std::vector<std::string>> piece_cn_colors() const;

    /// @brief 获取棋子红黑互换后的fen字符串
    /// @return 字符串
    std::string get_rb_fen() const;

    /// @brief 获取棋子位置左右互换后的fen字符串
    /// @return 字符串
    std::string get_lr_fen() const;

    /// @brief 获取坐标所对应的棋子编码
    /// @param x x轴坐标
    /// @param y y轴坐标
    /// @return 整数编码 0 代表空 7 代表将、帅
    int get_piece_id(int x, int y) const;

    /// @brief 获取坐标所对应棋子在棋盘数组序号编码
    /// @param x x轴坐标
    /// @param y y轴坐标
    /// @return 整数编码 0-6 代表红方棋子，7~13 代表黑方棋子，坐标棋子为空白，返回-1
    int get_piece_bid(int x, int y) const;

    // for rl feature

    /// @brief 移动前移动编码特征
    /// @param action 移动编码
    /// @return 三维(14 * 10 * 9)整数列表。反映移动棋子及吃子编码特征
    std::vector<std::vector<std::vector<int>>> getActionFeature(int action);

    /// @brief 使用棋子编号设置棋盘
    /// @param data 2d棋子编码，单元数值代表棋子编号，0代表空白
    /// @param to_play 下一步走子方 [1, 2]
    /// @param steps 步数
    /// @param continuous_uneaten 连续未吃子数量
    void set_pieces_by_2d(std::vector<std::vector<int>> data, int to_play = S_RED, int steps = 1, int continuous_uneaten = 0);

    /// @brief 棋盘棋子数字表达
    /// @param lr 是否左右互换
    /// @return 二维(10 * 9)整数列表
    // 10 * 9 第一维代表 y 轴坐标 第二维代表 x 轴坐标，交叉点数字代表棋子类型
    std::vector<std::vector<int>> get2d(bool lr = false);

    /// @brief 棋盘棋子数字表达
    /// @param lr 是否左右互换
    /// @return 三维(14 * 10 * 9)整数列表
    // 14 * 10 * 9 其中第一维代表棋子 红方棋子 0 - 6 黑方 7 -13 第二维代表 y 轴坐标 第三维代表 x 轴坐标
    std::vector<std::vector<std::vector<int>>> get3d(bool lr = false);

    /// @brief 棋子位置
    /// @param lr 是否左右互换
    /// @return 棋盘棋子对象列表
    std::vector<Piece> get_pieces(bool lr = false);

    // 当前棋盘上将、帅坐标
    Coord GetCoordOfKing(const Color &s) const;

    // 坐标所在位置的棋子价值【仅仅用于候选移动排序】
    int GetPiecesInfo(const Coord &coord) const;

    // 当前棋盘棋子统计信息
    GamePieceCount GetPiecesInfo() const;

    // 当前棋盘子力累积价值
    PiecesValue GetTotalValue();

    // 双方无子力进攻
    bool IsInsufficientMaterial();

    // 是否形成将帅照面
    bool IsFace2Face();

    // 当前棋盘对player而言是否处于将军状态
    bool IsCheck(const Color &player) const;

    // 被将死 【player指被将死的那一方】
    // 执行任何移动后被对手将军或导致将帅照面，即被将死
    bool IsCheckmate(const Color &player);

    // 一旦移动后是否会立即输棋
    bool immediately_loss_once_moved(Move &move) const;

    // 当前局面下可以一步杀死对手的移动
    // 如不存在，返回无效移动
    // 下一着不予考虑，即使对方填子延缓，最终被杀也不算，即一步杀
    Move get_one_step_kill_move() const;

    // 检查移动是否有效
    bool tryMove(const Move &move);

    virtual void on_repeat(size_t t, size_t times);

    // 执行走子 [不会对移动合法性进行检查]
    void DoMove(Move &move);

    // 专用于模拟运行
    void SimulateMove(Move &move);

    // 回退
    void undoMove();

    // 回退N步
    void undoNSteps(const int n);

    // 移动历史字符串 0001 格式

    /// @brief 移动历史字符串
    /// @return 字符串
    std::string get_move_history_string() const;

    /// @brief 带颜色、换行移动历史字符串
    /// @return 字符串
    std::string get_move_history_view_string() const;

    /// @brief 棋盘fen字符串表达
    /// @param include_moves 保护移动字符串
    /// @param simple 是否返回简单格式
    /// @param include_no_eat 是否包含连续未吃子数量
    /// @return 字符串
    std::string get_fen_string(bool include_moves = false, bool simple = false, bool include_no_eat = true);

    // ********* 候选移动 *********

    /// @brief 玩家所有棋子可能着法候选列表，包括走后导致自杀的移动
    /// @param player 走子方
    /// @return 移动列表
    moveVec_t GetCandidates(const Color &player) const;

    // 获取游戏方候选移动列表
    // `exclude`指示是否排除自杀移动
    moveVec_t GetCandidatesByPlayer(const Color &player, bool exclude = true) const;

    // 整数序号形式表达，当前玩家所有合法走子列表
    std::vector<int> legal_ations() const;

    /// @brief 当前玩家所有吃子移动列表
    /// @return 整数列表
    std::vector<int> eat_actions() const;

    // 从坐标出发的移动列表 排除掉无效、非法移动后
    moveVec_t GetCandidatesFrom(const Coord &start, bool exclude = true) const;

    // 所有下一步将军移动
    // 指定位置无效代表所有，否则只选取指定位置开始的部分
    moveVec_t GetCandidatesForCheck(const Color &player, const Coord start = EMPTY_COORD) const;

    // 游戏方所有吃子移动列表
    // `exclude`指示是否排除自杀移动
    moveVec_t GetCandidatesForEat(const Color &player, bool exclude = true) const;

    // 以目标坐标为吃对象的移动列表
    // `exclude`指示是否排除导致自杀的移动
    moveVec_t GetCandidatesForTargetEat(const Coord &tgt, bool exclude = false) const;

    // 指定位置开始的吃列表
    moveVec_t CandidatesForEatFrom(const Color &player, const Coord start = EMPTY_COORD) const;

    // 吃无根子候选【注意：已经剔除自杀移动】
    moveVec_t GetCandidatesForEatNoRoot(const Color &player, const Coord start = EMPTY_COORD) const;
};