#pragma once
#include <fstream>
#include <memory>
#include <list>
#include <queue>

#include "board.hpp"
#include "board_utils.hpp"
#include "utils.hpp"

// 中国象棋比赛规则2022版本
namespace rule2022
{
    /// @brief 先行方是否只有一个棋子移动
    /// @param hist 移动历史
    /// @return 如果先行方只有一个棋子移动，返回`真`，否则返回`假`
    bool is_only_one_zhuo(const moveVec_t &hist);

    /// @brief 目标棋子不能离线【TODO：需要观察修正】简单版本，作为联合捉的辅助分析。实际上，需要做杀模拟才能得出正确结论
    /// @param board 棋局
    /// @param tgt 检测坐标
    /// @return 如果目标不得离线，返回`真`，否则返回`假`
    bool can_not_offline(const Board &board, const Coord &tgt);

    /// @brief 截除尾部兑
    /// @param hist 移动历史
    /// @return 截除尾部兑后的移动历史
    moveVec_t get_trimed_tail_path(const moveVec_t &hist);

    /// @brief 判定移动历史是否为先行方联合捉子
    /// @param board 给定棋局
    /// @param hist 给定移动历史
    /// @return 返回`真`或`假`
    bool is_jointed_zhuo(const Board &board, const moveVec_t &hist);

    /// @brief 计算移动历史吃子差异【不包含将、帅】
    struct PieceDiff
    {
        // 存在过河兵、卒即升变，当随后一着非吃强子时，升变失效
        bool ascension = false;
        // 以下为得子数量，正数表示赢得，负数表示失去
        // 弱子数量
        int weak = 0;
        // 强子数量 车相当于2个炮
        int strong = 0;
        // 过河兵数量
        int pawn_cross_river = 0;

        std::vector<PieceInfo> hist_;

        /// @brief 更新
        /// @param p 棋子信息
        /// @param is_first 是否为先行方
        inline void update(const PieceInfo &p, bool is_first = true)
        {
            auto v = get_piece_value(p);
            if (is_first)
            {
                if (v == 2 * STRONG_VALUE)
                {
                    strong += 2;
                }
                else if (v == STRONG_VALUE)
                {
                    if (p.piece == PieceType::PAWN)
                    {
                        ascension = true;
                        pawn_cross_river += 1;
                    }
                    else
                    {
                        strong += 1;
                    }
                }
                else if (v == WEAK_VALUE)
                {
                    weak += 1;
                }
            }
            else
            {
                if (v == 2 * STRONG_VALUE)
                {
                    strong -= 2;
                }
                else if (v == STRONG_VALUE)
                {
                    if (p.piece == PieceType::PAWN)
                    {
                        ascension = true;
                        pawn_cross_river -= 1;
                    }
                    else
                    {
                        strong -= 1;
                    }
                }
                else if (v == WEAK_VALUE)
                {
                    weak -= 1;
                }
            }
            auto t = hist_.size();
            if (t >= 1)
            {
                auto prev = hist_.back();
                // 上一着为吃过河兵、卒，下一着非吃强子时
                if (ascension && get_piece_value(prev) == STRONG_VALUE && prev.piece == PieceType::PAWN && v < STRONG_VALUE)
                {
                    ascension = false;
                }
            }
            hist_.push_back(p);
        }

        /// @brief 过河兵卒是否产生升变
        /// @return 返回`真`或`假`
        inline bool is_ascension()
        {
            return ascension;
        }

        /// @brief 是否得子
        /// @return 返回`真`或`假`
        inline bool is_dz()
        {
            if (pawn_cross_river + strong >= 1)
            {
                // 以浮动价值的兵交换象，不算得子
                if (strong == 0 && weak < 0)
                {
                    return false;
                }
                return true;
            }
            else if (pawn_cross_river + strong == 0)
            {
                // 净得弱子
                if (weak >= 1)
                {
                    return true;
                }
            }
            return false;
        }
    };

    /// @brief 排序吃候选列表【排除吃将、帅、将军及无价值的棋子】
    /// @param eats 吃候选列表
    /// @param include_jj 是否包含将军
    /// @return 排序后的列表【棋子价值排序：车、马、炮、过河兵及其他】
    moveVec_t get_sorted_eats(const moveVec_t &eats, bool include_jj = false);

    // 序列中包含吃刚过河的兵或卒
    bool immediately_eat_just_cross_river_pawn(const moveVec_t &hist);

    // 吃子差
    PieceDiff path_difference(const moveVec_t &hist);

    // 判定序列是否得子
    bool is_path_dezi(const moveVec_t &hist);

    // 从移动历史中获取指定开始位置和长度的分部移动历史列表
    moveVec_t get_part_of_history(const moveVec_t &hist, size_t size, size_t start = 0);

    // 先行方移动历史的净收益
    int get_net_gain(const moveVec_t &hist);

    // 分离出将军、互吃二部分
    std::vector<moveVec_t> get_splited_history(const moveVec_t &hist);

    // 判定等值互换是否为捉
    // ➡️ 26.5 完整互吃后价值相当或得子者，按捉，得不偿失者，按闲
    // ➡️ 1. 做根子捉子
    // ➡️ 2. 被牵子捉子
    // ➡️ 3. 各吃各子的捉子
    bool is_equivalent_zhuo(const Board &board, const moveVec_t &zhuo_hist);

    struct Node : std::enable_shared_from_this<Node> // note: public inheritance
    {
        size_t priority = 1;
        size_t visit_count = 0;

        // 剪除标记
        bool cutted_ = false;
        // 剪除兄弟节点标记
        bool cutted_brothers_ = false;

        bool pass = false;
        bool stop = false;
        // 存储相对于先行方的得分
        int s_score = 0;
        float value = 0.0f;

        std::shared_ptr<Node> parent;                // 父节点指针
        std::vector<std::shared_ptr<Node>> children; // 子节点指针列表
        std::vector<Move> history;                   // 移动历史
        std::set<Move> child_move_set;               // 子节点移动集合

        std::shared_ptr<Node> getptr();

        // No public constructor, only a factory function,
        // so there's no way to have getptr return nullptr.
        [[nodiscard]] static std::shared_ptr<Node> create(const std::vector<Move> &hist)
        {
            // Not using std::make_shared<Node> because the c'tor is private.
            return std::shared_ptr<Node>(new Node(hist));
        }

        // Node(const Node &) = default;                // Copy constructor
        // Node(Node &&) = default;                     // Move constructor
        // ~Node(); // Destructor
        // Node &operator=(const Node &) = default; // Copy assignment
        // Node &operator=(Node &&) = default;      // Move assignment

        bool expanded() const;

        // 生成子节点
        std::shared_ptr<Node> gen_child(const Move &action);

        // 展开子节点
        void expand(const std::vector<Move> &actions);

        // 节点深度
        size_t depth() const;

        // 是否为根节点
        bool is_root() const;

        // 是否为叶子节点
        bool is_leaf() const;

        // 所有子节点都标记为截断
        bool all_child_cutted() const;

        // 存在任一有效的子节点
        bool has_any_valid_child() const;

        // 是否为终止节点
        // 1. 或者为叶子节点
        // 2. 非叶子节点，但所有子节点要么标记为cutted_，要么已访问
        bool is_terminal() const;

        // 当前节点的根节点
        // root -> 1 -> 2 -> 3 -> 4 -> 5 -> 6
        //     🔙
        // 返回
        // root
        std::shared_ptr<Node> root_node();

        // 节点所在的一级节点
        std::shared_ptr<Node> top1_node();

        // 返回向上`n`级祖先节点
        // 从当前节点向上3级
        // root -> 1 -> 2 -> 3 -> 4 -> 5 -> 6
        //                   ^
        // 返回
        // root -> 1 -> 2 -> 3
        std::shared_ptr<Node> nth_predecessor(size_t n);

        // 是否与节点为兄弟关系
        bool is_brother(const std::shared_ptr<Node> &node) const;

        // 选择指定移动的子节点
        std::shared_ptr<Node> select_child(const Move &action);

        // 从该节点中选择指定完整路径的后代节点
        std::shared_ptr<Node> select_posterity(const std::vector<Move> &hist);

        // 在已经访问过的子节点中，选择最大值的子节点
        std::shared_ptr<Node> select_max_child() const;

        // 在已经访问过的子节点中，选择最小值的子节点
        std::shared_ptr<Node> select_min_child() const;

        // 从子节点更新该节点状态信息
        void update();

        // 根据候选移动列表，生成任务节点列表，返回左叶节点
        std::shared_ptr<Node> gen_paths(const std::vector<Move> &branch,
                                        std::list<std::shared_ptr<Node>> &tasks);

        // 节点及上级节点是否标识为裁剪
        bool cutted() const;

        // 节点及上级节点是否标识为终止状态
        bool stopped() const;

        // 节点及上级节点是否标识为通过状态
        bool passed() const;

        // 以简化路径为标识符
        std::string identifier() const;

        // 该节点dot表达
        // 1. 该节点 node string
        // 2. 与父节点的边 edge string
        // 3. 终止点：值、状态
        std::string dot_string_node(Color predecessor = S_RED) const;

        // 自下而上为给定节点找到下一个尚未在映射表中出现，可重新开始遍历的顶点
        std::shared_ptr<Node> get_b2t_vertex(std::map<std::string, std::shared_ptr<Node>> m, std::shared_ptr<Node> b);

        // 整个节点树以路径为键，以节点为值映射表
        std::map<std::string, std::shared_ptr<Node>> get_root_tree_map();

        // 节点所在的根，其树dot字符串
        std::string dot_string_root_tree(Color predecessor = S_RED, std::string fname = "tree");

        // 路径
        std::string path() const;

        // 彩色路径
        std::string color_path(Color predecessor = S_RED) const;

        // 打印路径
        void print(Color predecessor = S_RED) const;

        // 节点详细信息
        std::string detail(Color predecessor = S_RED) const;

        // 显示节点详细信息
        void view_detail(Color predecessor = S_RED);

        // 显示节点树信息
        void view_tree(Color predecessor = S_RED);

        friend bool operator<(const Node &n1, const Node &n2)
        {
            if (n1.depth() == n2.depth())
            {
                return n1.priority < n2.priority;
            }
            else
            {
                return n1.depth() < n2.depth();
            }
        }

        // 显示时节点按移动比较
        struct NodeView
        {
            bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const
            {
                if (lhs->depth() == rhs->depth())
                {
                    return lhs->path() < rhs->path();
                }
                else
                {
                    return lhs->depth() < rhs->depth();
                }
            }
        };

    private:
        static std::set<std::string> m_paths_;
        Node(const std::vector<Move> &hist = {});
    };

    // 纯粹将军长度
    size_t get_jj_size(std::shared_ptr<Node> node_ptr);

    class Simulator
    {
    protected:
        helper::MyClock clock;
        bool completed_ = false;
        // 基数：1000 【单方除帅价值外，其余棋子合计值】
        // 千分之一
        float value_discout = 0.999f;
        int base_value = 0;
        size_t times_ = 0;
        size_t max_depth_ = SIMULATE_MAX_DEPTH;

    public:
        // 是否超过最大模拟次数
        bool exceeded = false;
        // 是否需要检查已经通过的待处理任务
        // 除将军得子模拟外，其余均不需要
        bool check_passed = false;
        // 存储与本方上一着相关吃列表
        // 便于测试
        std::map<std::string, moveVec_t> hist_eats;
        std::list<std::shared_ptr<Node>> tasks;
        Board init_board;
        Color player;
        Move start_ = EMPTY_MOVE;
        Move prohibit_ = PROHIBIT_MOVE;
        Coord tgt_ = EMPTY_COORD;
        std::shared_ptr<Node> root;
        Simulator(const Board &b_,
                  const Color &player_)
            : init_board{b_},
              player{player_}
        {
            root = Node::create({});
            clock.restart();
            tasks.clear();
            auto tv = init_board.GetTotalValue();
            // 以对手棋子总价值为基数【忽略将帅价值】
            // 防止分母出现零值
            base_value = (player == S_RED ? tv.black : tv.red) - KING_VALUE + 1;
        };

        virtual std::string title() = 0;

        /// @brief 清理待处理任务
        /// @param start_node 开始节点
        void remove_tasks(const std::shared_ptr<Node> &start_node);

        // 当不剪枝`passed`分支时，如节点所在的一级节点已经通过，且得子价值大于等于车时，停止模拟
        bool stop_simulate(const std::shared_ptr<Node> &node);

        // 是否应当早停
        virtual bool should_early_stop(const std::shared_ptr<Node> & /*node_ptr*/, const moveVec_t & /* cands*/, const Board & /*board*/) { return false; };

        // 展开左叶节点
        //             ⏹️
        //           ↙️ ⇣ ⋱
        //         ↙️ ⋱
        //       ↙️
        //    ✅

        virtual void evaluate(std::shared_ptr<Node> &node_ptr, const Board &board) = 0;

        // 反向传播最接近一级未终止的叶子节点
        // 如不存在则返回根节点
        //             ⏹️
        //           ↙️ ⇣ ⋱
        //         ↗↘️
        //       ↗    ⏹️(最近未访问的位置展开)
        //    ✅ ⤴️↙  ⇣ ⋱
        //        ↙⋱
        //      ↙
        //    ⭕(超过搜索深度，终止)

        //             ⏹️
        //           ↙️ ⇣ ⋱
        //         ↗↘️
        //       ↗    ⏹️
        //    ✅ ⤴️↙  ⇣ ⋱
        //        ↗↘️
        //      ↗   ⏹️(展开)
        //    ⭕⤴️
        // 反向传播：
        // 奇数深度节点(本方)，全部子节点通过即通过，任一子节点失败即失败
        // 偶数深度节点(对方)，任一子节点通过即通过，全部子节点失败即失败

        /// @brief 下一个任务
        /// @return 待处理任务[共享指针]
        std::shared_ptr<Node> next_task();

        /// @brief 设置要执行的开始移动
        /// @param move 指定开始移动
        virtual void set_start(Move move);

        /// @brief 设置排除的候选移动
        /// @param move 指定需要排除的移动
        void set_not_allowed(Move move);

        /// @brief 设置要吃子的目标坐标
        /// @param tgt 指定吃子目标坐标
        void set_target(Coord tgt);

        std::shared_ptr<Node> maxmin_path();

        virtual bool IsTrue() = 0;

        // 模拟次数
        inline size_t times() const { return times_; };

        // 显示当前待处理任务列表
        void view_tasks();

        // 排序后的将军候选
        // 1. 吃强子同时将军优先
        // 2. 将军棋子不被吃优先
        virtual moveVec_t get_check_cands(const Board &board, const Color &p);

        // 响应将军
        virtual moveVec_t check_response(const Board &board, const Color &p, const Move &last);

        // 输入节点及当前盘面，返回可能的移动
        virtual moveVec_t get_cands(const std::shared_ptr<Node> &node_ptr, const Board &board) = 0;

        // 根据候选移动生成待处理任务，获取指定节点的左叶节点
        std::shared_ptr<Node> select_left_leaf_node(std::shared_ptr<Node> node_ptr, const moveVec_t &cands);

        // 选择尚未访问的子节点
        std::shared_ptr<Node> select_not_visited_node(std::shared_ptr<Node> node_ptr);

        // 处理输入节点，返回下一个节点
        // 展开左叶节点
        //             ⏹️
        //           ↙️ ⇣ ⋱
        //         ↙️ ⋱
        //       ↙️
        //    ✅
        std::shared_ptr<Node> rollout(std::shared_ptr<Node> node_ptr);

        // 从根节点开始搜索最合理路径
        virtual const std::shared_ptr<Node> ReasonablePath(bool trimed = true) = 0;

        // 执行向上传播
        void backpropagate(std::shared_ptr<Node> &node_ptr);

        // 能否吃回指定坐标的棋子
        bool can_eat_back(moveVec_t &history, const Coord &tgt);

        // 局部向上传播到指定节点
        void partially_backpropagate(std::shared_ptr<Node> &start, std::shared_ptr<Node> &end);

        // 预先修复节点，剪除有胜负的尾部
        std::shared_ptr<Node> pre_fixed_node(const std::shared_ptr<Node> &node_ptr);

        // 从下至上修正节点
        std::shared_ptr<Node> backward_fixed_node(const std::shared_ptr<Node> &node_ptr);

        // 反向截断点（从下至上）
        std::shared_ptr<Node> get_backward_fixed_node(const std::shared_ptr<Node> &node_ptr);

        // 正向截断点（从上至下）
        std::shared_ptr<Node> get_forward_fixed_node(const std::shared_ptr<Node> &node_ptr);

        // 从上至下修正节点
        // std::shared_ptr<Node> forward_fixed_node(const std::shared_ptr<Node> &node_ptr);

        // 检查并修复节点
        virtual std::shared_ptr<Node> fixed_node(std::shared_ptr<Node> node_ptr);

        // 最终结果节点
        // 1. 剪除尾部非吃部分
        // 2. 前端已经得子，剪除尾部兑
        std::shared_ptr<Node> final_fixed_node(const std::shared_ptr<Node> &node_ptr);

        // 运行模拟
        void run();
    };

    /// @brief 模拟先行方将军或连续将军至杀死对手。NB::`停着`并不算杀
    class ShaSimulator : public Simulator
    {
    public:
        ShaSimulator(const Board &b_,
                     const Color &player_)
            : Simulator(b_, player_)
        {
            // 根节点中有任一子节点通过，不再尝试其他着法
            check_passed = false;
        };

        std::string title() override final { return "杀着模拟器"; };

        void evaluate(std::shared_ptr<Node> &node_ptr, const Board &board) override final;

        bool IsTrue() override final;

        const std::shared_ptr<Node> ReasonablePath(bool trimed = true) override final;

        /// @brief 指定节点、棋局下的候选列表
        /// @param node_ptr 节点
        /// @param board 棋局
        /// @return 候选列表
        moveVec_t get_cands(const std::shared_ptr<Node> &node_ptr, const Board &board) override final;
    };

    // 互吃模拟器
    // 模拟搜索当前棋局下，是否存在通过互吃可得子的路径
    // 备注：
    // 1. 第一步只能为吃，且非将军
    // 2. 吃子并不排除自杀
    // 3. 任何一方采取自杀移动，对手即选择吃将、帅结束模拟
    // 4. 任何一方只要存在杀，即返回杀作为唯一候选
    class ChiSimulator : public Simulator
    {
    private:
        moveVec_t starts_;
        moveVec_t checked_starts_;

    public:
        ChiSimulator(const Board &b_,
                     const Color &player_)
            : Simulator(b_, player_)
        {
            // 根节点中有任一子节点通过，不再尝试其他着法
            check_passed = false;

            hist_eats.clear();

            if (b_.next_player() == player)
            {
                hist_eats["root"] = related_eat_after_moved(b_, true);
            }
            else
            {
                hist_eats["root"] = related_eat_after_moved(b_, false);
            }
            // 此时清空移动历史记录
            init_board.clear_history();
        };

        std::string title() override final { return "互吃模拟器"; };

        // 设置开始移动列表
        void set_start_moves(const moveVec_t &starts);

        // 设置已经检查过的开始移动列表
        void set_checked_start_moves(const moveVec_t &checked);

        void set_start(Move move) override final;

        // 将得子标准更改为决定得子，即净收益>=1
        void evaluate(std::shared_ptr<Node> &node_ptr, const Board &board) override final;

        bool IsTrue() override final;

        std::shared_ptr<Node> fixed_node(std::shared_ptr<Node> node_ptr) override final;

        const std::shared_ptr<Node> ReasonablePath(bool trimed = true) override final;

        // 首着不得将军
        // 排除吃无价值的棋子，如未过河的兵、卒
        // 排除吃将、帅
        moveVec_t get_cands(const std::shared_ptr<Node> &node_ptr, const Board &board) override final;
    };

    // 将军得子模拟器
    // 用途：
    //      将军得子模拟，直至任务列表为空或找到得子着法
    // 备注：
    // 1. 先手的吃必须与将军有必然联系，即吃为将军导致而非期初就存在
    // 2. 先手将军、后手应将
    // 3. 先手期初中本已经存在的吃【非将】，在将军后不被列入候选，除非处于互吃阶段
    class JdzSimulator : public Simulator
    {
    private:
        moveVec_t init_eats_;

    public:
        JdzSimulator(const Board &b_,
                     const Color &player_)
            : Simulator(b_, player_)
        {
            // 节点即使通过，仍然需要检查是否存在可吃强子而选择了将军
            check_passed = true;
            // 最多连续四次将军
            max_depth_ = 5;
            hist_eats.clear();
            // 此时清空移动历史记录
            init_board.clear_history();
            auto eats = init_board.GetCandidatesForEat(player);
            for (auto m : eats)
            {
                if (!init_board.HasRootProtected(m))
                {
                    init_eats_.push_back(m);
                }
            }
        };

        std::string title() override final { return "将军得子模拟器"; };

        void set_start(Move move) override final;

        void evaluate(std::shared_ptr<Node> &node_ptr, const Board &board) override final;

        /// @brief 先行方是否应当早停
        /// @param node_ptr 基准节点
        /// @param cands 候选移动列表
        /// @param board 棋局
        /// @return 确信早停返回`真`，否则返回`假`
        bool should_early_stop(const std::shared_ptr<Node> &node_ptr, const moveVec_t &cands, const Board &board) override final;

        const std::shared_ptr<Node> ReasonablePath(bool trimed = true) override final;

        // 双向修复节点，剔除不合理部分
        std::shared_ptr<Node> fixed_node(std::shared_ptr<Node> node_ptr) override final;

        bool IsTrue() override final;

        // 能避免被对手再次将军的应将优先
        moveVec_t check_response(const Board &board, const Color &p, const Move &last) override final;

        /// @brief 指定节点和棋局，输出相应移动候选列表
        /// @param node_ptr 给定节点
        /// @param board 给定棋局
        /// @return 候选移动列表。先行将军后的吃，限定为可净吃子，即要么吃无根子，要么所吃之子棋子价值大于本身价值
        moveVec_t get_cands(const std::shared_ptr<Node> &node_ptr, const Board &board) override final;
    };
}