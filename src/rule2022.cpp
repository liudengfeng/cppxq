#include "rule2022.hpp"

namespace rule2022
{
    bool is_only_one_zhuo(const moveVec_t &hist)
    {
        // 长度小于2始终返回true
        for (size_t i = 2; i < hist.size(); i = i + 2)
        {
            if (hist[i].from != hist[i - 2].to)
            {
                return false;
            }
        }
        return true;
    }

    moveVec_t get_trimed_tail_path(const moveVec_t &hist)
    {
        if (hist.empty())
        {
            return hist;
        }
        moveVec_t head, tail, remains;
        remains = hist;
        auto t = remains.size();
        for (size_t i = 0; i < t; i++)
        {
            head = get_part_of_history(hist, t - i - 1);
            // fmt::print("i={} head={}\n", i, head);
            if (head.empty())
            {
                break;
            }
            tail = get_part_of_history(remains, remains.size() - head.size(), t - i - 1);
            // 此前已经得子，舍弃尾部的兑子
            if (get_net_gain(head) >= WEAK_VALUE && get_net_gain(tail) == 0)
            {
                remains = get_part_of_history(remains, remains.size() - tail.size());
            }
        }
        return remains;
    }

    bool can_not_offline(const Board &board, const Coord &tgt)
    {
        Board b0 = board.clone();
        auto info = b0.pieces()[tgt.id()];
        assertm(!info.IsEmpty(), "判定不能离线时，给定坐标必须有棋子");
        auto cands0 = b0.GetCandidatesFrom(tgt, false);
        auto cands1 = b0.GetCandidatesFrom(tgt, true);
        // 包含自杀移动时
        if (cands0.size() > cands1.size())
        {
            return true;
        }
        for (auto m : cands1)
        {
            if (b0.immediately_loss_once_moved(m))
            {
                return true;
            }
        }
        return false;
    }

    bool is_jointed_zhuo(const Board &board, const moveVec_t &hist)
    {
        // 走子后将军，且有其他子将军
        if (hist.front().is_jointed_check())
        {
            return true;
        }
        // 图11-1 图11-3 象本身为假根保护
        if (board.IsFakeRootProtected(hist.front().to))
        {
            return true;
        }
        auto tgt = hist.front().to;
        // 参考图44-4 以炮换车
        if (hist.size() == 2 && board.HasRootProtected(hist.front()) && get_piece_value(hist[0].info.tgt) > get_piece_value(hist[1].info.tgt))
        {
            return false;
        }
        // 首先检查截断尾部兑后的路径
        auto trimed = get_trimed_tail_path(hist);
        if (trimed.size() == hist.size())
        {
            if (trimed.size() <= 2)
            {
                // 有根保护为联合捉
                // 参考图图47-1 红车捉马 务必使用移动判定根保护
                if (board.HasRootProtected(hist.front()))
                {
                    return true;
                }
                else
                {
                    if (can_not_offline(board, tgt))
                    {
                        return true;
                    }
                }
            }
            else
            {
                if (!is_only_one_zhuo(hist))
                {
                    return true;
                }
            }
        }
        else
        {
            // 有根保护为联合捉
            if (board.HasRootProtected(hist.back()))
            {
                return true;
            }
            else
            {
                if (can_not_offline(board, tgt))
                {
                    return true;
                }
            }
        }
        return false;
    }

    moveVec_t get_sorted_eats(const moveVec_t &eats, bool include_jj)
    {
        moveVec_t cands;
        if (!include_jj)
        {
            for (auto m : eats)
            {
                if (m.info.tgt.piece == PieceType::ROOK && !m.is_check())
                {
                    cands.push_back(m);
                }
            }
            for (auto m : eats)
            {
                if (!m.is_check() && (m.info.tgt.piece == PieceType::CANNON || m.info.tgt.piece == PieceType::HORSE))
                {
                    cands.push_back(m);
                }
            }
            for (auto m : eats)
            {
                if (!m.is_check() && is_cross_river_pawn(m.info.tgt))
                {
                    cands.push_back(m);
                }
            }
            for (auto m : eats)
            {
                if (!m.is_check() && get_piece_value(m.info.tgt) == WEAK_VALUE)
                {
                    cands.push_back(m);
                }
            }
        }
        else
        {
            for (auto m : eats)
            {
                if (m.info.tgt.piece == PieceType::ROOK)
                {
                    cands.push_back(m);
                }
            }
            for (auto m : eats)
            {
                if ((m.info.tgt.piece == PieceType::CANNON || m.info.tgt.piece == PieceType::HORSE))
                {
                    cands.push_back(m);
                }
            }
            for (auto m : eats)
            {
                if (is_cross_river_pawn(m.info.tgt))
                {
                    cands.push_back(m);
                }
            }
            for (auto m : eats)
            {
                if (get_piece_value(m.info.tgt) == WEAK_VALUE)
                {
                    cands.push_back(m);
                }
            }
        }
        return cands;
    }

    bool immediately_eat_just_cross_river_pawn(const moveVec_t &hist)
    {
        size_t loc = 99;
        for (size_t i = 0; i < hist.size(); i++)
        {
            auto p = hist[i].info.tgt;
            if (p.piece == PieceType::PAWN && is_just_cross_river_pawn(p))
            {
                loc = i;
                break;
            }
        }
        if (loc != 99)
        {
            if (hist.size() == 1)
            {
                // 简化处理：当列表只有一个，假设兵、卒刚过河
                return true;
            }
            else
            {
                auto p = hist[loc - 1].info.src;
                // 必须检查前一步为未过河的兵卒
                return p.piece == PieceType::PAWN && !is_cross_river_pawn(p);
            }
        }
        return false;
    }

    PieceDiff path_difference(const moveVec_t &hist)
    {
        PieceDiff diff;
        bool add = true;
        for (auto m : hist)
        {
            // if (m.info.tgt.piece == PieceType::KING || m.info.s_score != 0)
            // {
            //     throw std::runtime_error("得子序列中不得包含分出胜负移动!");
            // }
            diff.update(m.info.tgt, add);
            add = !add;
        }
        return diff;
    }

    bool is_path_dezi(const moveVec_t &hist)
    {
        // 立即吃掉刚过河的兵不算得子
        // fmt::print("{} {} hist={}\n", immediately_eat_just_cross_river_pawn(hist), get_net_gain(hist), hist);
        // 直接取胜等同得子
        if (!hist.empty() && hist.back().info.s_score == KING_VALUE)
        {
            return true;
        }
        // 由于升变其值设定为弱子价值
        if (immediately_eat_just_cross_river_pawn(hist) && get_net_gain(hist) >= WEAK_VALUE)
        {
            return false;
        }
        // if (hist.size() == 1 && is_just_cross_river_pawn(hist.front().info.tgt))
        // {
        //     return false;
        // }
        auto diff = path_difference(hist);
        return diff.is_dz();
    }

    moveVec_t get_part_of_history(const moveVec_t &hist, size_t size, size_t start)
    {
        moveVec_t res;
        if (size == 0)
        {
            return {};
        }
        if (size > hist.size() || start > (hist.size() - 1))
        {
            std::string msg = fmt::format("要截取的序列={}\n1. 超长错误={}({})\n2. 定位错误={}({})\n",
                                          hist, size > hist.size(), size, start > (hist.size() - 1), start);
            throw std::out_of_range(msg);
        }
        for (size_t i = start; i < start + size; i++)
        {
            res.push_back(hist[i]);
        }
        return res;
    }

    int get_net_gain(const moveVec_t &hist)
    {
        int res = 0;
        int sign = 1;
        for (auto m : hist)
        {
            res += get_piece_value(m.info.tgt) * sign;
            sign *= -1;
        }
        // 只有尾部记录输赢部分才附加
        if (!hist.empty() && std::abs(hist.back().info.s_score) == KING_VALUE)
        {
            if (hist.size() % 2 == 1)
            {
                res += hist.back().info.s_score;
            }
            else
            {
                res -= hist.back().info.s_score;
            }
        }
        return res;
    }

    std::vector<moveVec_t> get_splited_history(const moveVec_t &hist)
    {
        std::vector<moveVec_t> res;
        moveVec_t jjs, cs;
        jjs.clear();
        cs.clear();
        auto t0 = hist.size();
        // 分离将军、应将部分【双方均未吃子】
        for (size_t i = 0; i < t0; i++)
        {
            if (i % 2 == 0)
            {
                continue;
            }
            // 任何一方吃子即退出
            if (hist[i - 1].is_eat() || hist[i].is_eat())
            {
                break;
            }
            // 前部
            jjs.push_back(hist[i - 1]);
            jjs.push_back(hist[i]);
        }
        assertm(jjs.size() % 2 == 0, "将军部分应成对");
        res.push_back(jjs);
        // 互吃部分
        for (size_t i = jjs.size(); i < t0; i++)
        {
            // 后部
            cs.push_back(hist[i]);
        }
        res.push_back(cs);
        return res;
    }

    // 给定期初棋盘、移动历史判定是否为各捉各子
    bool _is_e2e(const Board &board, const moveVec_t &zhuo_hist)
    {
        std::vector<std::pair<PieceInfo, PieceInfo>> zhuoes;
        std::pair<PieceInfo, PieceInfo> p;
        auto r_etas = board.GetCandidatesForEat(S_RED, true);
        auto b_etas = board.GetCandidatesForEat(S_BLACK, true);
        for (auto m : r_etas)
        {
            zhuoes.emplace_back(m.info.src, m.info.tgt);
        }
        for (auto m : b_etas)
        {
            zhuoes.emplace_back(m.info.src, m.info.tgt);
        }
        // 记录棋子变化路径
        std::map<Coord, PieceInfo> path;
        for (auto m : zhuo_hist)
        {
            p = std::make_pair(m.info.src, m.info.tgt);
            // 原本就在期初棋盘吃列表
            if (contains(zhuoes, p))
            {
                // 记录被捉子的移动
                path[m.to] = m.info.src;
                continue;
            }
            try
            {
                p = std::make_pair(m.info.src, path.at(m.to));
                if (!contains(zhuoes, p))
                {
                    return false;
                }
            }
            catch (const std::out_of_range &e)
            {
                return false;
            }
        }
        return true;
    }

    bool is_equivalent_zhuo(const Board &board, const moveVec_t &zhuo_hist)
    {
        // 非空路径净收益为0
        if (!zhuo_hist.empty() && get_net_gain(zhuo_hist) == 0)
        {
            // 图22-1 做“根”子捉子
            // 参考图27-1 被“牵”子捉子
            // 参考图16 各吃各子的捉子
            if (board.HasRootProtected(zhuo_hist[0].from, zhuo_hist[1].to) ||
                board.IsPinned(zhuo_hist[0].from) || _is_e2e(board, zhuo_hist))
            {
                return true;
            }
        }
        return false;
    }

    Node::Node(const std::vector<Move> &hist) : history(hist)
    {
        if (hist.empty())
        {
            parent = nullptr;
        }
        // std::cout << "创建节点" << fmt::format("{}", hist)
        //           << " (" << reinterpret_cast<uintptr_t>(this) << ")\n";
    }

    bool Node::expanded() const
    {
        return !this->children.empty();
    }

    std::shared_ptr<Node> Node::gen_child(const Move &action)
    {
        auto hist = this->history;
        hist.push_back(action);
        auto result = child_move_set.insert(action);
        if (result.first == child_move_set.end())
        {
            throw std::out_of_range("子节点路径重复");
        }
        auto child_ptr = Node::create(hist);
        child_ptr->parent = getptr();
        return child_ptr;
    }

    void Node::expand(const moveVec_t &actions)
    {
        size_t t = 1;
        for (const auto a : actions)
        {
            auto child_sptr = this->gen_child(a);
            child_sptr->priority = t;
            children.push_back(child_sptr);
            t += 1;
            // std::cout << "父节点" << fmt::format("{}", this->history)
            //           << " (" << reinterpret_cast<uintptr_t>(child_sptr->parent.get()) << ")  "
            //           << "添加子节点 " << fmt::format("{}", child_sptr->history)
            //           << " (" << reinterpret_cast<uintptr_t>(child_sptr.get()) << ")\n";
        }
    }

    std::shared_ptr<Node> Node::getptr()
    {
        return shared_from_this();
    }

    size_t Node::depth() const
    {
        return history.size();
    }

    bool Node::is_root() const
    {
        return parent == nullptr && this->history.empty();
    }

    bool Node::is_leaf() const
    {
        return this->parent != nullptr && this->children.empty();
    }

    bool Node::all_child_cutted() const
    {
        return !is_leaf() && std::all_of(
                                 this->children.begin(), this->children.end(), [](auto c)
                                 { return c->cutted_; });
    }

    bool Node::has_any_valid_child() const
    {
        return !is_leaf() && std::any_of(
                                 this->children.begin(), this->children.end(), [](auto c)
                                 { return !c->cutted_ && c->visit_count >= 1; });
    }

    bool Node::is_terminal() const
    {
        return is_leaf() || std::all_of(this->children.begin(), this->children.end(), [](auto c)
                                        { return c->cutted_ || c->visit_count >= 1; });
    }

    std::shared_ptr<Node> Node::root_node()
    {
        if (this->is_root())
        {
            return getptr();
        }
        else
        {
            auto p = this->parent;
            while (p && p->depth() >= 1)
            {
                p = p->parent;
            }
            return p;
        }
    }

    std::shared_ptr<Node> Node::top1_node()
    {
        if (this->depth() < 2)
        {
            return getptr();
        }
        else
        {
            auto p = this->parent;
            while (p->depth() >= 2)
            {
                p = p->parent;
            }
            return p;
        }
    }

    std::shared_ptr<Node> Node::nth_predecessor(size_t n)
    {
        assertm(this->depth() >= n, fmt::format("节点深度不得小于{}", n));
        std::shared_ptr<Node> node = this->getptr();
        for (size_t i = 0; i < n; i++)
        {
            node = node->parent;
        }
        return node;
    }

    // Node::~Node()
    // {
    //     std::cout << "毁损节点"
    //               << " (" << reinterpret_cast<uintptr_t>(this) << ")\n";
    // }

    bool Node::is_brother(const std::shared_ptr<Node> &node) const
    {
        return node->parent == this->parent && node->history != this->history;
    }

    std::shared_ptr<Node> Node::select_child(const Move &action)
    {
        auto hist = this->history;
        hist.push_back(action);
        auto result = std::find_if(this->children.begin(), this->children.end(), [=](const std::shared_ptr<Node> &n)
                                   { return n->history == hist; });
        if (result != this->children.end())
        {
            return *result;
        }
        else
        {
            throw std::out_of_range(fmt::format("不存在路径为{}的子节点", hist));
        }
    }

    std::shared_ptr<Node> Node::select_posterity(const std::vector<Move> &hist)
    {
        assertm(hist.size() >= (this->history.size() + 1), "必须为该节点的后代节点");
        auto c = this->root_node();
        for (size_t i = 0; i < hist.size(); i++)
        {
            c = c->select_child(hist[i]);
            if (c->history == hist)
            {
                return c;
            }
        }
        return nullptr;
    }

    std::shared_ptr<Node> Node::select_max_child() const
    {
        std::vector<std::shared_ptr<Node>> vec;
        std::copy_if(this->children.begin(), this->children.end(),
                     std::back_inserter(vec),
                     [](const std::shared_ptr<Node> c)
                     { return !c->cutted_ && c->visit_count >= 1; });

        if (vec.empty())
        {
            return nullptr;
        }
        return *std::max_element(vec.begin(), vec.end(), [&](const auto &a, const auto &b)
                                 { return a->value == b->value ? a->priority > b->priority : a->value < b->value; });
    }

    std::shared_ptr<Node> Node::select_min_child() const
    {
        std::vector<std::shared_ptr<Node>> vec;
        std::copy_if(this->children.begin(), this->children.end(),
                     std::back_inserter(vec),
                     [](const std::shared_ptr<Node> c)
                     { return !c->cutted_ && c->visit_count >= 1; });

        if (vec.empty())
        {
            return nullptr;
        }
        return *std::min_element(vec.begin(), vec.end(), [&](const auto &a, const auto &b)
                                 { return a->value == b->value ? a->priority < b->priority : a->value < b->value; });
    }

    void Node::update()
    {
        this->visit_count += 1;
        std::vector<std::shared_ptr<Node>> vec;
        std::copy_if(this->children.begin(), this->children.end(),
                     std::back_inserter(vec),
                     [](const std::shared_ptr<Node> c)
                     { return !c->cutted_; });

        if (vec.empty())
        {
            auto msg = fmt::format("无有效叶子节点，无法更新!\n当前路径：\n{}\n", this->path());
            throw std::out_of_range(msg);
        }

        // 更新状态
        if (this->depth() % 2 == 0)
        {
            this->pass = std::any_of(vec.begin(), vec.end(),
                                     [](const auto &p)
                                     { return p->pass; });
            this->stop = std::all_of(vec.begin(), vec.end(), [](const auto &p)
                                     { return p->stop; });
        }
        else
        {
            this->pass = std::all_of(vec.begin(), vec.end(),
                                     [](const auto &p)
                                     { return p->pass; });
            this->stop = std::any_of(vec.begin(), vec.end(),
                                     [](const auto &p)
                                     { return p->stop; });
        }

        if (this->depth() % 2 == 0)
        {
            auto c_max = this->select_max_child();
            this->value = c_max->value;
            this->s_score = c_max->s_score;
        }
        else
        {
            auto c_min = this->select_min_child();
            this->value = c_min->value;
            this->s_score = c_min->s_score;
        }
    }

    std::shared_ptr<Node> Node::gen_paths(const std::vector<Move> &branch,
                                          std::list<std::shared_ptr<Node>> &tasks)
    {
        expand(branch);
        auto t = children.size();
        // 首项不需要将其放入任务队列
        // 注意采用叠加方式添加
        for (size_t i = 0; i < t; i++)
        {
            if (i == 0)
            {
                continue;
            }
            tasks.push_front(children[t - i]);
        }
        // 始终返回首个子节点
        return children.front();
    }

    bool Node::cutted() const
    {
        if (this->cutted_)
        {
            return true;
        }
        auto p = this->parent;
        while (p)
        {
            if (p->cutted_)
            {
                return true;
            }
            p = p->parent;
        }
        return false;
    }

    bool Node::stopped() const
    {
        if (this->stop)
        {
            return true;
        }
        auto p = this->parent;
        while (p)
        {
            if (p->depth() % 2 == 0)
            {
                if (std::all_of(p->children.begin(), p->children.end(), [](const auto &p)
                                { return p->stop && !p->cutted_; }))
                {
                    return true;
                }
            }
            else
            {
                if (std::any_of(p->children.begin(), p->children.end(), [](const auto &p)
                                { return p->stop && !p->cutted_; }))
                {
                    return true;
                }
            }
            p = p->parent;
        }
        return false;
    }

    bool Node::passed() const
    {
        if (this->pass)
        {
            return true;
        }
        auto p = this->parent;
        while (p)
        {
            if (p->depth() % 2 == 0)
            {
                if (std::any_of(p->children.begin(), p->children.end(), [](const auto &p)
                                { return p->pass && !p->cutted_; }))
                {
                    return true;
                }
            }
            else
            {
                if (std::all_of(p->children.begin(), p->children.end(), [](const auto &p)
                                { return p->pass && !p->cutted_; }))
                {
                    return true;
                }
            }
            p = p->parent;
        }
        return false;
    }

    std::string Node::identifier() const
    {
        std::string path_str = "root";
        for (const auto &m : history)
        {
            path_str = fmt::format("{}{}", path_str, m.toString());
        }
        return path_str;
    }

    std::string Node::dot_string_node(Color predecessor) const
    {
        std::string name, shape, arrowhead, edge_label, xlabel, style, node_color, v_label, edge_color, dot;
        name = this->identifier();
        shape = "record";
        xlabel = "";
        arrowhead = "normal";
        if (this->depth() == 0)
        {
            node_color = "black";
        }
        else if (this->depth() % 2 == 1)
        {
            node_color = predecessor == S_RED ? "red" : "blue";
        }
        else
        {
            node_color = predecessor == S_RED ? "blue" : "red";
        }
        if (is_root())
        {
            dot = "root [label = \"开始\" color = \"black\" shape=\"octagon\"];\n";
        }
        else
        {
            std::string node_template = "{} [shape=\"{}\" label=\"{}\" color = \"{}\"];\n";
            std::string edge_template = "{} -> {} [label = \"{}\" color = \"{}\" style = \"{}\"  xlabel = \"{}\" arrowhead = \"{}\" tooltip=\"{}\"];\n";
            edge_label = this->history.back().toString();
            v_label = fmt::format("{: .2f}", this->value * 100.0f);
            // 叶子节点
            if (is_leaf())
            {
                if (this->visit_count == 1)
                {
                    shape = "ellipse";
                    edge_color = this->pass ? "limegreen" : "magenta";
                    style = this->pass ? "solid" : "dashed";
                    if (this->pass)
                    {
                        v_label = fmt::format("{: .2f}✅", this->value * 100.0f);
                    }
                    else
                    {
                        v_label = fmt::format("{: .2f}❎", this->value * 100.0f);
                    }
                    if (!this->parent->cutted_ && this->cutted_)
                    {
                        xlabel = "✂️";
                    }
                }
                else
                {
                    shape = "plain";
                    v_label = "♻️";
                    edge_color = "lightgray";
                    style = "dotted";
                    arrowhead = "curve";
                }
            }
            // 非叶子节点
            else
            {
                if (!this->parent->cutted_ && this->cutted_)
                {
                    edge_color = this->pass ? "limegreen" : "magenta";
                    style = this->pass ? "solid" : "dashed";
                    xlabel = "✂️";
                }
                else
                {
                    xlabel = "";
                    edge_color = this->pass ? "limegreen" : "magenta";
                    style = this->pass ? "solid" : "dashed";
                }
            }

            if (this->cutted())
            {
                edge_color = "gray";
                // style = "dotted";
                style = "dashed";
            }
            else
            {
                if (this->all_child_cutted())
                {
                    if (this->pass)
                    {
                        v_label = fmt::format("{: .2f}✅", this->value * 100.0f);
                    }
                    else
                    {
                        v_label = fmt::format("{: .2f}❎", this->value * 100.0f);
                    }
                }
            }
            dot = fmt::format(node_template, name, shape, v_label, node_color);
            dot += fmt::format(edge_template, this->parent->identifier(), name,
                               edge_label,
                               edge_color,
                               style,
                               xlabel,
                               arrowhead,
                               edge_label);
        }
        return dot;
    }

    std::shared_ptr<Node> Node::get_b2t_vertex(std::map<std::string, std::shared_ptr<Node>> m, std::shared_ptr<Node> b)
    {
        auto p = b->parent;
        while (p)
        {
            for (auto n : p->children)
            {
                // 当没有在映射中出现，返回
                auto search = m.find(n->path());
                if (search == m.end())
                {
                    return n;
                }
            }
            p = p->parent;
        }
        return nullptr;
    }

    std::map<std::string, std::shared_ptr<Node>> Node::get_root_tree_map()
    {
        std::map<std::string, std::shared_ptr<Node>> m;
        auto n = root_node();
        // 访问顶点位置次数等于其子节点数量即终止
        while (n)
        {
            // 首先需要添加顶点
            m[n->path()] = n;
            while (!n->children.empty())
            {
                n = n->children.front();
                m[n->path()] = n;
            }
            // 找不到时返回空指针
            n = get_b2t_vertex(m, n);
        }
        return m;
    }

    std::string Node::dot_string_root_tree(Color predecessor, std::string fname)
    {
        std::string dot = "##\"使用graphviz显示模拟树\"\n"
                          "##使用命令生成文件后，用浏览器查阅文件:";
        dot += fmt::format("\"dot -Tsvg {}.dot -o {}.svg\"\n", fname, fname);
        dot += "digraph tree {\n"
               "fontsize=\"8\"\n"
               "node [shape=\"box\"]\n"
               "edge [];\n"
               "rankdir=fliplr\n";
        auto m = get_root_tree_map();
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            dot += it->second->dot_string_node(predecessor);
        }
        return dot + "}";
    }

    std::string Node::path() const
    {
        std::string path_str = "root";
        for (const auto &m : history)
        {
            path_str = fmt::format("{} -> {:^4}", path_str, m.toString());
        }
        return path_str;
    }

    std::string Node::color_path(Color predecessor) const
    {
        std::string str;
        std::string move_str;
        str = fmt::format(fg(fmt::color::light_blue), "root");
        size_t i = 0;
        for (const auto &m : history)
        {
            i += 1;
            str += " -> ";
            move_str = fmt::format("{:^4}", m.toString());
            if (i % 2 == 1)
            {
                str += fmt::format(predecessor == S_RED ? fg(fmt::color::crimson) : fg(fmt::color::green), "{}", move_str);
            }
            else
            {
                str += fmt::format(predecessor == S_RED ? fg(fmt::color::green) : fg(fmt::color::crimson), "{}", move_str);
            }
        }
        // 分别代表是否通过、是否访问、是否剪枝
        std::string flag1, flag2, flag3;
        if (this->pass)
        {
            flag1 = "✅";
        }
        else if (this->stop)
        {
            // flag1 = "❌";
            flag1 = "❎";
        }
        else
        {
            flag1 = "❓";
        }

        if (visit_count >= 1)
        {
            flag2 = "⭕";
        }
        else
        {
            flag2 = "⛔";
        }

        if (is_leaf())
        {
            flag3 = "🍁";
        }
        else
        {
            if (this->cutted_)
            {
                flag3 = "✂️";
            }
            else
            {
                flag3 = "";
            }
        }
        // 符号最大长度为7
        str = fmt::format("{}{:^4}{:^4}{:<7}", str, flag1, flag2, flag3);
        return str;
    }

    void Node::print(Color predecessor) const
    {
        fmt::print("{}\n", color_path(predecessor));
    }

    std::string Node::detail(Color predecessor) const
    {
        // 正号以空白
        return fmt::format("{} 值 ={: .6f} 得分={} 访问 ={:>4} 子节点 ={:>2} 优先度 ={:>3} 通过={:>5} 停止={:>5} 裁剪={:>5}",
                           this->color_path(predecessor),
                           this->value,
                           this->s_score,
                           this->visit_count,
                           this->children.size(),
                           this->priority,
                           this->pass,
                           this->stop,
                           this->cutted_);
    }

    void Node::view_detail(Color predecessor)
    {
        // 正号以空白
        fmt::print("{}\n", this->detail(predecessor));
    }

    void Node::view_tree(Color predecessor)
    {
        fmt::print("节点树:\n");
        view_detail(predecessor);
        auto p = parent;
        while (p)
        {
            p->view_detail(predecessor);
            p = p->parent;
        }
        fmt::print("\n\n");
    }

    size_t get_jj_size(std::shared_ptr<Node> node_ptr)
    {
        size_t t = 0;
        auto hist = node_ptr->history;
        for (auto m : hist)
        {
            if (m.is_eat())
            {
                break;
            }
            t += 1;
        }
        if (t % 2 == 1)
        {
            t -= 1;
        }
        assertm(t % 2 == 0, "纯粹将军序列长度一定为偶数");
        return t;
    }

    std::shared_ptr<Node> Simulator::maxmin_path()
    {
        // 自上而下
        auto parent = root;
        auto child = parent;
        // 确保根节点能够正常处理
        while (parent)
        {
            if (parent->depth() % 2 == 0)
            {
                child = parent->select_max_child();
            }
            else
            {
                child = parent->select_min_child();
            }
            if (child == nullptr)
            {
                // 当子节点不存在有效访问时，返回空指针。退回到父节点
                child = parent;
                break;
            }
            else if (child->is_leaf())
            {
                break;
            }
            parent = child;
        }
        return child;
    }

    bool Simulator::stop_simulate(const std::shared_ptr<Node> &node)
    {
        if (!check_passed)
        {
            if (!node->history.empty() && node->top1_node()->pass && node->top1_node()->s_score >= 2 * STRONG_VALUE)
            {
                return true;
            }
        }
        return false;
    }

    void Simulator::remove_tasks(const std::shared_ptr<Node> &start_node)
    {
        auto start_path = start_node->history;
        auto is_start_with = [start_path](const std::shared_ptr<Node> n)
        {
            if (n->history.size() < start_path.size())
            {
                return false;
            }
            auto t = start_path.size();
            for (size_t i = 0; i < t; i++)
            {
                if (start_path[i] != n->history[i])
                {
                    return false;
                }
            }
            return true;
        };
        tasks.remove_if([=](const std::shared_ptr<Node> n)
                        { return is_start_with(n); });
    }

    std::shared_ptr<Node> Simulator::next_task()
    {
        if (tasks.empty())
        {
            return nullptr;
        }
        auto node_ptr = tasks.front();
        tasks.pop_front();
        if (this->check_passed)
        {
            if (node_ptr->passed())
            {
                // fmt::print("{} 根得分 = {}\n", node_ptr->path(), root->s_score);
                // 当根节点没有得强子，必须尝试其他一级节点
                if (root->s_score < STRONG_VALUE && node_ptr->depth() == 1)
                {
                    return node_ptr;
                }
                else if (node_ptr->depth() % 2 == 1 && node_ptr->depth() > 1)
                {
                    auto m = node_ptr->history.back();
                    auto brothers = node_ptr->parent->children;
                    // 将军后续节点即使通过，也需要尝试直接吃子
                    auto has_jj = std::any_of(brothers.begin(), brothers.end(), [m](auto b)
                                              { return b->visit_count >= 1 && b->history.back() != m && b->history.back().is_check(); });
                    // 如等值吃，其中一种已经通过，只尝试其中一种即可
                    auto has_tried = std::none_of(brothers.begin(), brothers.end(), [m](auto b)
                                                  { return b->history.back().is_eat() && b->pass &&
                                                           b->visit_count >= 1 && b->history.back() != m &&
                                                           get_piece_value(m.info.tgt) == get_piece_value(b->history.back().info.tgt); });

                    // 在先行方节点上修复错误使用将军而未吃子
                    if (m.is_eat() && get_piece_value(m.info.tgt) >= WEAK_VALUE)
                    {
                        if (has_jj && has_tried)
                        {
                            // fmt::print("任务节点{}\n", node_ptr->path());
                            node_ptr->cutted_brothers_ = true;
                            return node_ptr;
                        }
                    }
                }
                return next_task();
            }
            else if (node_ptr->stopped())
            {
                return next_task();
            }
            else
            {
                return node_ptr;
            }
        }
        else
        {
            if (node_ptr->passed() || node_ptr->stopped())
            {
                return next_task();
            }
            else
            {
                return node_ptr;
            }
        }
    }

    void Simulator::run()
    {
        auto node_ptr = root;
        times_ = 0;
        while (true)
        {
            node_ptr = rollout(node_ptr);
            // fmt::print("{} {}\n", title(), node_ptr->path());
            times_ += 1;
            // 返回根节点直接退出
            if (node_ptr->is_root())
            {
                break;
            }
            if (times_ >= MAX_NUM_OF_MOCK)
            {
                exceeded = true;
                break;
            }
            node_ptr = fixed_node(node_ptr);
            // fmt::print("{} {}\n", title(), node_ptr->path());
            // node_ptr->view_tree(player);

            // 根节点停止时才停止。即任何一级子节点即使通过，也需要尝试其他一级子节点
            if (root->stop)
            {
                break;
            }

            if (tasks.empty())
            {
                break;
            }

            node_ptr = next_task();
            // fmt::print("下一任务 {} {}\n", title(), node_ptr->path());
            // node_ptr->view_tree(player);

            if (node_ptr == nullptr)
            {
                break;
            }
        }

        completed_ = true;

        if (USE_DEBUG)
        {
            fmt::print("{} {}\n\n", title(), clock.summary());
        }
    }

    void Simulator::set_start(Move move)
    {
        assertm(!completed_, "务必在模拟前设置开始移动");
        start_ = move;
    }

    void Simulator::set_not_allowed(Move move)
    {
        assertm(!completed_, "务必在模拟前设置禁止移动");
        prohibit_ = move;
    }

    void Simulator::set_target(Coord tgt)
    {
        assertm(!completed_, "务必在模拟前设置吃子目标");
        tgt_ = tgt;
    }

    void Simulator::view_tasks()
    {
        fmt::print("待处理任务：{:>5}个\n", tasks.size());
        for (auto t : tasks)
        {
            // t->print(player);
            t->view_tree(player);
        }
        fmt::print("\n\n");
    }

    moveVec_t Simulator::get_check_cands(const Board &board, const Color &p)
    {
        moveVec_t cands;
        auto jjs = board.GetCandidatesForCheck(p);
        // 将军同时吃强子优先
        for (auto jj : jjs)
        {
            if (jj.is_eat() && get_piece_value(jj.info.tgt) >= STRONG_VALUE)
            {
                cands.push_back(jj);
            }
        }
        // 将军的棋子不会被吃优先
        for (auto jj : jjs)
        {
            if (!contains(cands, jj))
            {
                auto b1 = board.clone();
                b1.SetPlayer(p);
                b1.DoMove(jj);
                auto eb = b1.GetCandidatesForEat(OPPONENT(p));
                if (eb.empty())
                {
                    cands.push_back(jj);
                }
            }
        }
        // 其余部分
        for (auto jj : jjs)
        {
            if (!contains(cands, jj))
            {
                cands.push_back(jj);
            }
        }
        return cands;
    }

    moveVec_t Simulator::check_response(const Board &board, const Color &p, const Move &last)
    {
        moveVec_t cands;
        std::set<Coord> jjs;
        for (auto p : last.info.jj_after_moved)
        {
            jjs.insert(p.coord);
        }
        bool king_first = false;
        for (auto p : last.info.jj_after_moved)
        {
            if (p.piece == PieceType::CANNON || p.piece == PieceType::ROOK)
            {
                king_first = true;
            }
        }
        auto resp = board.GetCandidatesByPlayer(p);
        // 吃将军的棋子
        for (auto m : resp)
        {
            if (m.is_eat() && contains(jjs, m.to))
            {
                cands.push_back(m);
            }
        }
        // 将帅躲闪
        if (king_first)
        {
            for (auto m : resp)
            {
                if (!contains(cands, m) && m.info.src.piece == PieceType::KING)
                {
                    cands.push_back(m);
                }
            }
        }
        // 填子【非吃】
        for (auto m : resp)
        {
            if (!contains(cands, m) && !m.is_eat())
            {
                cands.push_back(m);
            }
        }
        // 其他应将着法
        for (auto m : resp)
        {
            if (!contains(cands, m))
            {
                cands.push_back(m);
            }
        }
        return cands;
    }

    void Simulator::backpropagate(std::shared_ptr<Node> &node_ptr)
    {
        auto parent = node_ptr->parent;
        // 向上传播
        if (node_ptr->visit_count == 0)
        {
            // 首次传播设置访问次数
            node_ptr->visit_count = 1;
        }
        else if (node_ptr->has_any_valid_child())
        {
            // 在该节点上使用有效子节点的值更新
            node_ptr->update();
        }
        // 状态更新
        while (parent)
        {
            parent->update();
            parent = parent->parent;
        }
    }

    bool Simulator::can_eat_back(moveVec_t &history, const Coord &tgt)
    {
        auto b1 = init_board.clone();
        b1.SetPlayer(player);
        // 由于模拟时重复一次即判和
        for (auto &m : history)
        {
            b1.SimulateMove(m);
            if (b1.is_game_ended())
            {
                return false;
            }
        }
        auto eats = b1.GetCandidatesForEat(b1.next_player(), true);
        return std::any_of(eats.begin(), eats.end(), [tgt](const Move &m)
                           { return m.to == tgt; });
    }

    void Simulator::partially_backpropagate(std::shared_ptr<Node> &start, std::shared_ptr<Node> &end)
    {
        // fmt::print("partially_backpropagate start={} end={}\n", start->path(), end->path());
        // 设置访问次数
        start->visit_count = 1;
        auto parent = start->parent;
        // 状态更新
        while (parent)
        {
            if (parent->visit_count >= 1 || parent->history == end->history)
            {
                break;
            }
            parent->update();
            parent = parent->parent;
        }
    }

    std::shared_ptr<Node> Simulator::select_left_leaf_node(std::shared_ptr<Node> node_ptr, const moveVec_t &cands)
    {
        node_ptr->expand(cands);
        // 插入到前端
        tasks.insert(tasks.begin(), node_ptr->children.begin(), node_ptr->children.end());
        tasks.pop_front();
        return node_ptr->children.front();
    }

    std::shared_ptr<Node> Simulator::select_not_visited_node(std::shared_ptr<Node> node_ptr)
    {
        for (auto c : node_ptr->children)
        {
            if (c->visit_count != 0)
            {
                continue;
            }
            return c;
        }
        return nullptr;
    }

    std::shared_ptr<Node> Simulator::pre_fixed_node(const std::shared_ptr<Node> &node_ptr)
    {
        if (node_ptr->is_root())
        {
            return node_ptr;
        }
        else
        {
            if (std::abs(node_ptr->history.back().info.s_score) == KING_VALUE)
            {
                auto t = node_ptr->depth();
                if (t >= 3)
                {
                    auto f_n = node_ptr->nth_predecessor(2);
                    if (!f_n->history.back().is_check())
                    {
                        return node_ptr->nth_predecessor(2);
                    }
                }
                else if (t == 2)
                {
                    return node_ptr->nth_predecessor(2);
                }
            }
        }
        return node_ptr;
    }

    std::shared_ptr<Node> Simulator::get_backward_fixed_node(const std::shared_ptr<Node> &node_ptr)
    {
        std::shared_ptr<Node> fixed = node_ptr;
        std::shared_ptr<Node> head_node;
        moveVec_t head, tail, remains;
        int tail_v = 0;
        // 非受迫性受损
        bool cond;
        auto jj_size = get_jj_size(node_ptr);
        remains = node_ptr->history;
        auto t = remains.size();
        if (t > jj_size)
        {
            for (size_t i = 0; i < t - jj_size; i++)
            {
                head = get_part_of_history(node_ptr->history, t - i - 1);
                tail = get_part_of_history(remains, remains.size() - head.size(), t - i - 1);
                tail_v = get_net_gain(tail);
                // 尾部受损
                cond = tail_v < 0;
                if (!head.empty())
                {
                    // 非将军的受损
                    cond &= !head.back().is_check();
                    head_node = root->select_posterity(head);
                }
                else
                {
                    head_node = root;
                }
                // fmt::print("{} {} {} tail_v={} 截断 = {}\n", i, head, tail, tail_v, cond);
                // 注意使用值判断：节点可能被访问，但不一定更新过数值
                // 当节点值已经更新，即退出
                if (head_node->value != 0.0f)
                {
                    break;
                }
                if (cond)
                {
                    remains = get_part_of_history(remains, remains.size() - tail.size());
                }
            }
        }
        if (remains.empty())
        {
            fixed = root;
        }
        else
        {
            fixed = root->select_posterity(remains);
        }
        return fixed;
    }

    std::shared_ptr<Node> Simulator::get_forward_fixed_node(const std::shared_ptr<Node> &node_ptr)
    {
        std::shared_ptr<Node> head_node, head_node_child;
        std::shared_ptr<Node> fixed;
        moveVec_t head, head_child, tail, head1, head2;
        int head_v = 0;
        int path_v = get_net_gain(node_ptr->history);
        // fmt::print("输入 = {} 收益 = {}\n", node_ptr->path(), path_v);
        auto jj_size = get_jj_size(node_ptr);
        auto t = node_ptr->depth();
        // 确保首尾路径非空
        if (t <= jj_size + 2)
        {
            return node_ptr;
        }
        for (size_t i = jj_size; i < t + 1; i++)
        {
            head = get_part_of_history(node_ptr->history, i);
            head_child = head;
            if (head.empty())
            {
                head_node = root;
            }
            else
            {
                head_node = root->select_posterity(head);
            }
            tail = get_part_of_history(node_ptr->history, t - head.size(), i);
            if (head.empty())
            {
                head_child.push_back(tail[0]);
                head_node_child = root->select_posterity(head_child);
            }
            else
            {
                if (tail.empty())
                {
                    break;
                }
                else
                {
                    head_child.push_back(tail[0]);
                    head_node_child = root->select_posterity(head_child);
                }
            }
            head_v = get_net_gain(head);
            // 限定在未访问节点中裁剪
            // 正向搜索的终点为未访问
            // if (head_node_child->visit_count == 0 && !head.empty())
            if (!head.empty() && head_node_child->value == 0.0f)
            // if (!head.empty() && head_node_child->visit_count == 0)
            {
                auto is_sc = tail.size() >= 3 && get_piece_value(tail[0].info.tgt) < get_piece_value(tail[1].info.tgt);
                // 如先手采取行动减少收益则退出
                if (head.size() % 2 == 0)
                {
                    // 非受迫下减少收益
                    auto case1 = path_v < head_v;
                    // 非受迫下送吃后并没有增加路径收益
                    auto case2 = is_sc && !(path_v > head_v);
                    // if (!head.back().is_check() && case2)
                    // {
                    //     fmt::print("先手送吃 head = {} head_v = {} path_v = {} 差异 = {}\n", head, head_v, path_v, path_v - head_v);
                    // }
                    if (!head.back().is_check() && (case1 || case2))
                    {
                        // fmt::print("先手 case1 = {} case2 = {}\n", case1, case2);
                        break;
                    }
                }
                // 如对手采取行动增加收益则退出
                else
                {
                    // 非受迫下增加路径收益
                    auto case1 = path_v > head_v;
                    // 送吃后并没有减少路径收益
                    auto case2 = is_sc && !(path_v < head_v);
                    // if (!head.back().is_check() && case2)
                    // {
                    //     fmt::print("后手送吃 head = {} head_v = {} path_v = {} 差异 = {}\n", head, head_v, path_v, path_v - head_v);
                    // }
                    if (!head.back().is_check() && (case1 || case2))
                    {
                        break;
                    }
                }
            }
        }
        if (head.empty())
        {
            fixed = root;
        }
        else
        {
            fixed = root->select_posterity(head);
        }
        return fixed;
    }

    std::shared_ptr<Node> Simulator::final_fixed_node(const std::shared_ptr<Node> &node_ptr)
    {
        if (node_ptr->is_root() || (node_ptr->depth() >= 1 && std::abs(node_ptr->history.back().info.s_score) == KING_VALUE))
        {
            return node_ptr;
        }
        // auto jj_size = get_jj_size(node_ptr);
        moveVec_t head, tail, remains;
        remains = node_ptr->history;
        // 剔除尾部吃无价值棋子
        while (!remains.empty())
        {
            if (get_piece_value(remains.back().info.tgt) != 0)
            {
                break;
            }
            remains.pop_back();
        }
        // 剔除尾部兑
        // 如果尾部不影响最终结论，剔除尾部
        // root -> 5534 -> 3339 -> 4839 -> 2234 => root -> 5534
        auto t = remains.size();
        auto path_v = get_net_gain(remains);
        auto diff = path_difference(remains);
        if (path_v != 0 && diff.is_dz())
        {
            for (size_t i = 0; i < t; i++)
            {
                head = get_part_of_history(node_ptr->history, i + 1);
                tail = get_part_of_history(node_ptr->history, t - head.size(), head.size());
                if (head.back().is_eat() && !tail.empty() && head.back().to != tail.front().to &&
                    (get_net_gain(head) == path_v || (get_net_gain(tail) >= 0 && get_net_gain(head) > get_net_gain(tail))))
                {
                    remains = head;
                    break;
                }
            }
        }
        // 偶数长度的得子，尾部不影响最终得子结论，剪除尾部【但含有过河兵例外】
        // 参考图28-2 root -> 2728 -> 5257
        // 参考图01-1 root -> 5547 -> 6947 -> 5466 -> 8766 吃回例外
        auto s = remains.size();
        if (remains.size() >= 2 && remains.size() % 2 == 0 && diff.pawn_cross_river == 0 && get_net_gain(remains) >= WEAK_VALUE && get_net_gain(get_part_of_history(remains, remains.size() - 1)) >= WEAK_VALUE)
        {
            if (remains[s - 2].to != remains[s - 1].to)
            {
                remains.pop_back();
            }
        }
        if (remains.empty())
        {
            return root;
        }
        else
        {
            auto node = root->select_posterity(remains);
            return node;
        }
    }

    std::shared_ptr<Node> Simulator::fixed_node(std::shared_ptr<Node> node_ptr)
    {
        backpropagate(node_ptr);
        return node_ptr;
    }

    std::shared_ptr<Node> Simulator::rollout(std::shared_ptr<Node> node_ptr)
    {
        // fmt::print("{} 输入路径 {}\n", title(), node_ptr->path());
        std::vector<Move> cands;
        auto b1 = init_board.clone();
        b1.SetPlayer(player);
        // 必须清除历史记录，步数重新从1开始
        b1.clear_history();

        // 由于模拟时重复一次即判和
        bool flag = false;
        for (auto &m : node_ptr->history)
        {
            b1.SimulateMove(m);
            // b1.show_board(true, title());
            if (b1.is_game_ended())
            {
                // 发生在尾部
                flag = true;
                break;
            }
        }

        while (!flag && node_ptr->depth() <= max_depth_ * 2)
        {
            if (!node_ptr->expanded())
            {
                cands = get_cands(node_ptr, b1);

                if (cands.empty())
                {
                    break;
                }
                node_ptr = select_left_leaf_node(node_ptr, cands);
            }
            else
            {
                node_ptr = select_not_visited_node(node_ptr);
            }

            b1.SimulateMove(node_ptr->history.back());

            if (b1.is_game_ended())
            {
                break;
            }
        }
        // b1.show_board(true, "结束");
        // TODO:将军得子评估经常出现错误，待查
        try
        {
            evaluate(node_ptr, b1);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            node_ptr->value = 0.0f;
            node_ptr->pass = false;
        }
        return node_ptr;
    }

    const std::shared_ptr<Node> ShaSimulator::ReasonablePath(bool /*trimed*/)
    {
        if (!completed_)
        {
            run();
        }
        if (USE_DEBUG)
        {
            std::ofstream out("tree_sha.dot");
            out << root->dot_string_root_tree(player, "tree_sha");
            out.close();
        }
        if (exceeded)
        {
            // 超出最大模拟次数，返回跟节点，标记失败
            root->pass = false;
            return root;
        }
        return maxmin_path();
    }

    bool ShaSimulator::IsTrue()
    {
        // 使用根节点的通过属性
        auto n = this->ReasonablePath();
        return root->pass && n->pass;
    }

    moveVec_t ShaSimulator::get_cands(const std::shared_ptr<Node> &node_ptr, const Board &board)
    {
        Move sha = EMPTY_MOVE;
        moveVec_t cands;
        auto t = node_ptr->depth();
        sha = board.get_one_step_kill_move();
        if (sha.IsValid())
        {
            if (sha != prohibit_)
            {
                return {sha};
            }
            else
            {
                return {};
            }
        }
        else
        {
            if (t == 0)
            {
                cands = board.GetCandidatesForCheck(player);
            }
            else
            {
                auto last = node_ptr->history.back();
                // 先行方将军
                if (t % 2 == 0)
                {
                    cands = board.GetCandidatesForCheck(player);
                }
                // 后手方应将
                else
                {
                    cands = check_response(board, board.next_player(), last);
                }
            }
        }
        if (t % 2 == 0)
        {
            // 针对先行方而言，剔除禁止移动
            cands.erase(std::remove_if(cands.begin(), cands.end(),
                                       [=](const Move &m)
                                       {
                                           return prohibit_ == m;
                                       }),
                        cands.end());

            // 针对先行方而言，剔除反复无效将军
            if (t >= 2)
            {
                auto prev = node_ptr->history[t - 2];
                if (prev.is_other_check())
                {
                    auto p = prev.FT();
                    // fmt::print("{} {}\n", node_ptr->path(), p);
                    cands.erase(std::remove_if(cands.begin(), cands.end(),
                                               [=](const Move &m)
                                               {
                                                   return m == p;
                                               }),
                                cands.end());
                }
            }
        }
        return cands;
    }

    void ShaSimulator::evaluate(std::shared_ptr<Node> &node_ptr, const Board &board)
    {
        if (node_ptr->history.empty())
        {
            node_ptr->stop = true;
            return;
        }
        // 节点深度越短值越大
        auto t = node_ptr->depth();
        auto expected = player == S_RED ? 1 : -1;
        int game_result = board.final_result();
        // 忽略中间吃子价值
        if (game_result == expected)
        {
            node_ptr->value = 1.0f;
            node_ptr->pass = true;
        }
        else
        {
            node_ptr->stop = true;
            if (game_result == -expected || game_result == 0)
            {
                // 杀模拟对平局标记为负，防止出现重复将军
                node_ptr->value = -1.0f;
            }
            else
            {
                node_ptr->value = 0.0f;
            }
        }
        // 长度越长，价值越小
        node_ptr->value *= std::pow(value_discout, t - 1);
    }

    void ChiSimulator::set_start_moves(const moveVec_t &starts)
    {
        assertm(!completed_, "务必在模拟前设置开始移动");
        starts_ = starts;
    }

    void ChiSimulator::set_checked_start_moves(const moveVec_t &checked)
    {
        assertm(!completed_, "务必在模拟前设置开始移动");
        checked_starts_ = checked;
    }

    void ChiSimulator::set_start(Move move)
    {
        auto msg = fmt::format("互吃模拟已经取消设置开始移动({})，请使用`set_target`", move.toString());
        throw std::runtime_error(msg);
    }

    moveVec_t ChiSimulator::get_cands(const std::shared_ptr<Node> &node_ptr, const Board &board)
    {
        Move sha = EMPTY_MOVE;
        moveVec_t cands, eats, related;
        auto t = node_ptr->depth();
        if (t == 0)
        {
            // 如指定目标坐标
            if (tgt_.on_board())
            {
                eats = board.GetCandidatesForTargetEat(tgt_, false);
            }
            else
            {
                // 目标坐标无效时，才适用
                if (!starts_.empty())
                {
                    eats = starts_;
                }
                else
                {
                    related = hist_eats["root"];
                    eats = board.GetCandidatesForEat(player, false);
                    if (!checked_starts_.empty())
                    {
                        eats.erase(std::remove_if(eats.begin(), eats.end(),
                                                  [=](const Move &m)
                                                  {
                                                      return contains(checked_starts_, m);
                                                  }),
                                   eats.end());
                    }
                }
            }
            // 按目标价值排序【从大到小】
            eats = get_sorted_eats(eats, false);

            // 首着不得为将军，即使为吃
            // 优先相关吃
            for (auto m : related)
            {
                if (!m.is_check() && m.info.tgt.piece != PieceType::KING && get_piece_value(m.info.tgt) >= WEAK_VALUE && contains(eats, m))
                {
                    auto it = std::find(eats.begin(), eats.end(), m);
                    if (it != eats.end())
                    {
                        cands.push_back(*it);
                    }
                }
            }
            // 其余部分
            for (auto m : eats)
            {
                if (m.info.tgt.piece == PieceType::KING || get_piece_value(m.info.tgt) < WEAK_VALUE || m.is_check())
                {
                    continue;
                }
                if (!contains(cands, m))
                {
                    cands.push_back(m);
                }
            }
            // fmt::print("根节点 {} 候选 {}\n", title(), cands);
        }
        else
        {
            auto hist = node_ptr->history;
            auto last = hist.back();
            sha = board.get_one_step_kill_move();
            // 存在杀时
            if (sha.IsValid())
            {
                if (sha != prohibit_)
                {
                    return {sha};
                }
                else
                {
                    return {};
                }
            }
            else
            {
                if (last.is_check())
                {
                    cands = check_response(board, board.next_player(), last);
                }
                else
                {
                    // 排除自杀移动
                    cands = board.GetCandidatesForEat(board.next_player(), true);
                    cands = get_sorted_eats(cands, true);
                }
            }
        }
        if (t % 2 == 0)
        {
            // 针对先行方而言，剔除禁止移动
            cands.erase(std::remove_if(cands.begin(), cands.end(),
                                       [=](const Move &m)
                                       {
                                           return prohibit_ == m;
                                       }),
                        cands.end());
        }
        return cands;
    }

    void ChiSimulator::evaluate(std::shared_ptr<Node> &node_ptr, const Board &board)
    {
        // 评估
        float value = 0.0f;
        auto t = node_ptr->depth();
        auto game_result = board.final_result();
        auto expected = player == S_RED ? 1 : -1;
        bool is_draw = game_result == 0;
        auto gain = get_net_gain(node_ptr->history);
        if (game_result == expected)
        {
            if (!node_ptr->history.empty())
            {
                node_ptr->history.back().info.s_score = KING_VALUE;
            }
            node_ptr->pass = true;
            gain += KING_VALUE;
        }
        else if (game_result == -expected)
        {
            if (!node_ptr->history.empty())
            {
                node_ptr->history.back().info.s_score = -KING_VALUE;
            }
            node_ptr->stop = true;
            gain -= KING_VALUE;
        }
        else if (is_draw)
        {
            if (!node_ptr->history.empty())
            {
                node_ptr->history.back().info.s_score = -KING_VALUE;
            }
            node_ptr->history.back().info.s_draw = true;
            node_ptr->stop = true;
            gain -= KING_VALUE;
        }
        else
        {
            // 由于互吃与相关吃存在密切联系，即优先相关吃来模拟，只要得子即可，不需要提高标准
            if (is_path_dezi(node_ptr->history))
            {
                node_ptr->pass = true;
            }
            else if (gain < 0)
            {
                node_ptr->stop = true;
            }
        }
        value = static_cast<float>(gain) / static_cast<float>(base_value);
        node_ptr->value = value * std::pow(value_discout, t - 1);
    }

    std::shared_ptr<Node> ChiSimulator::fixed_node(std::shared_ptr<Node> node_ptr)
    {
        std::shared_ptr<Node> to_cut_node;
        auto jj_s = get_jj_size(node_ptr);
        assertm(jj_s == 0, "吃模拟纯粹将军长度应为0");
        auto fixed = node_ptr;
        // fmt::print("\n初始 = {}\n", node_ptr->path());
        fixed = pre_fixed_node(node_ptr);
        // fmt::print("处理 = {}\n", fixed->path());
        // 首先反向，然后正向
        fixed = get_backward_fixed_node(fixed);
        // fmt::print("反向 = {}\n", fixed->path());
        fixed = get_forward_fixed_node(fixed);
        // fmt::print("正向 = {}\n", fixed->path());
        if (node_ptr->history.size() > fixed->history.size())
        {
            to_cut_node = fixed->select_child(node_ptr->history[fixed->depth()]);
            to_cut_node->cutted_ = true;
            // fmt::print("剪除 = {}\n\n", to_cut_node->path());
            // 清理待处理任务
            remove_tasks(to_cut_node);

            fixed = to_cut_node->parent;
            auto fixed_t = fixed->history.size();
            auto fixed_gain = get_net_gain(fixed->history);

            // 非叶子节点 --> 叶子节点
            if (fixed->all_child_cutted())
            {
                if (is_path_dezi(fixed->history))
                {
                    fixed->pass = true;
                }
                // 注意：互吃只有在失子时才停止
                else if (fixed_gain < 0)
                {
                    fixed->stop = true;
                }
                fixed->value = static_cast<float>(fixed_gain) / static_cast<float>(base_value) * std::pow(value_discout, fixed_t >= 1 ? fixed_t - 1 : 0);
            }
        }

        // 向上传播
        if (node_ptr->history.size() > fixed->history.size())
        {
            partially_backpropagate(node_ptr, fixed);
        }

        if (!fixed->is_root() && fixed->history.back().info.s_draw)
        {
            backpropagate(fixed->parent);
        }
        else
        {
            // 正常传播叶子节点
            backpropagate(fixed);
        }
        // fixed->view_tree(player);
        return fixed;
    }

    const std::shared_ptr<Node> ChiSimulator::ReasonablePath(bool trimed)
    {
        if (!completed_)
        {
            run();
        }

        if (USE_DEBUG)
        {
            std::ofstream out("tree_chi.dot");
            out << root->dot_string_root_tree(player, "tree_chi");
            out.close();
        }
        if (exceeded)
        {
            // 超出最大模拟次数，返回跟节点，标记失败
            root->pass = false;
            return root;
        }
        // 最大最小选出的路径，使用原始属性
        auto n = maxmin_path();
        // fmt::print("{},maxmin_path={} value={}\n", title(), n->path(), get_net_gain(n->history));
        if (trimed)
        {
            n = final_fixed_node(n);
            // fmt::print("{},maxmin_path={} value={}\n", title(), n->path(), get_net_gain(n->history));
            // 在此标识联合捉
            if (n->history.size() >= 1)
            {
                if (std::abs(n->history.back().info.s_score) == KING_VALUE)
                {
                    n->history.front().info.is_jointed = true;
                }
                else
                {
                    if (n->pass)
                    {
                        n->history.front().info.is_jointed = is_jointed_zhuo(init_board, n->history);
                    }
                }
            }
        }
        auto hist = n->history;
        if (!hist.empty())
        {
            // 重新修正
            auto v = get_net_gain(hist);
            if (v >= WEAK_VALUE)
            {
                n->pass = is_path_dezi(hist);
                n->value = static_cast<float>(v) / static_cast<float>(base_value) * std::pow(value_discout, hist.size() >= 1 ? hist.size() - 1 : 0);
            }
            else if (v == 0)
            {
                // fmt::print("{} 等值交换 {}\n", title(), n->path());
                if (is_equivalent_zhuo(init_board, n->history))
                {
                    n->pass = true;
                }
            }
            else
            {
                n = root;
            }
        }
        return n;
    }

    bool ChiSimulator::IsTrue()
    {
        auto n = this->ReasonablePath();
        if (n->is_root())
        {
            return false;
        }
        else
        {
            return n->pass;
        }
    }

    bool JdzSimulator::should_early_stop(const std::shared_ptr<Node> &node_ptr, const moveVec_t &cands, const Board &board)
    {
        auto t = node_ptr->depth();
        auto history = node_ptr->history;
        if (t % 2 == 1)
        {
            auto v = get_net_gain(history);
            auto tgt = history.back().to;
            bool cl = true;
            // 无法吃回
            auto ceb = std::none_of(cands.begin(), cands.end(), [tgt](const Move &m)
                                    { return m.to == tgt; });
            // 图28-2 抽将得强子
            if (v >= STRONG_VALUE && ((history.back().is_other_check() && history.back().is_eat()) ||
                                      (!history.back().is_check() && history.back().is_eat())))
            {
                cl = std::none_of(cands.begin(), cands.end(), [v](const Move &m)
                                  { return m.is_eat() && get_piece_value(m.info.tgt) > v; });
                return ceb && cl;
            }
            else if (v >= WEAK_VALUE && !history.back().is_check() && history.back().is_eat())
            {
                // 无法令先行受损
                for (auto m : cands)
                {
                    if (m.is_eat())
                    {
                        if (board.HasRootProtected(m))
                        {
                            if (get_piece_value(m.info.src) < get_piece_value(m.info.tgt))
                            {
                                cl = false;
                                break;
                            }
                        }
                        else
                        {
                            if (get_piece_value(m.info.tgt) > v)
                            {
                                cl = false;
                                break;
                            }
                        }
                    }
                }
                return ceb && cl;
            }
        }
        return false;
    }

    const std::shared_ptr<Node> JdzSimulator::ReasonablePath(bool trimed)
    {
        if (!completed_)
        {
            run();
        }
        if (USE_DEBUG)
        {
            std::ofstream out("tree_jdz.dot");
            out << root->dot_string_root_tree(player, "tree_jdz");
            out.close();
        }
        if (exceeded)
        {
            // 超出最大模拟次数，返回跟节点，标记失败
            root->pass = false;
            return root;
        }
        // 最大最小选出的路径，使用原始属性
        auto n = maxmin_path();
        // n->view_tree(player);
        auto hist = n->history;
        auto v = get_net_gain(hist);
        // fmt::print("{},maxmin_path={} v={} pass={}\n", title(), n->path(), v, n->pass);
        if (v <= 0 && (!hist.empty() && hist.back().info.s_score != KING_VALUE))
        {
            root->pass = false;
            return root;
        }
        if (trimed)
        {
            // fmt::print("最终路径\n");
            // n->print(player);
            n = final_fixed_node(n);
            // 在此标识联合捉
            if (n->history.size() >= 1)
            {
                if (std::abs(hist.back().info.s_score) == KING_VALUE)
                {
                    n->history.front().info.is_jointed = true;
                }
                else
                {
                    if (n->pass)
                    {
                        n->history.front().info.is_jointed = is_jointed_zhuo(init_board, n->history);
                    }
                }
            }
        }
        // n->print(player);
        // fmt::print("\n\n");
        auto t = n->depth();
        n->value = static_cast<float>(v) / static_cast<float>(base_value) * std::pow(value_discout, t - 1);
        // 重新修正
        n->pass = get_net_gain(hist) >= WEAK_VALUE || (!hist.empty() && hist.back().info.s_score == KING_VALUE);
        return n;
    }

    bool JdzSimulator::IsTrue()
    {
        auto n = this->ReasonablePath();
        if (n != nullptr && n->pass)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void JdzSimulator::set_start(Move move)
    {
        auto msg = fmt::format("将军得子模拟已经取消设置开始移动({})", move.toString());
        throw std::runtime_error(msg);
    }

    moveVec_t JdzSimulator::check_response(const Board &board, const Color &p, const Move &last)
    {
        moveVec_t cands;
        if (last.is_check())
        {
            // 首先吃
            cands = board.GetCandidatesForEat(p);
            auto resp = board.GetCandidatesByPlayer(p);
            auto b1 = board.clone();
            b1.SetPlayer(p);
            for (auto &m : resp)
            {
                if (contains(cands, m))
                {
                    continue;
                }
                b1.DoMove(m);
                // 走后令对手无法将军优先
                auto jjs = b1.GetCandidatesForCheck(OPPONENT(p));
                if (jjs.empty())
                {
                    cands.push_back(m);
                }
                b1.undoMove();
            }
            // 添加其余部分
            for (auto &m : resp)
            {
                if (!contains(cands, m))
                {
                    cands.push_back(m);
                }
            }
        }
        // board.show_board(true, "应将");
        // fmt::print("{}\n", cands);
        return cands;
    }

    moveVec_t JdzSimulator::get_cands(const std::shared_ptr<Node> &node_ptr, const Board &board)
    {
        std::vector<Move> cands, eats, related;
        // 一步杀包含吃将、帅、将死
        auto sha = board.get_one_step_kill_move();
        auto hist = node_ptr->history;
        auto t = hist.size();
        auto next_player = board.next_player();
        if (t == 0)
        {
            if (start_.IsValid())
            {
                cands = {start_};
            }
            else
            {
                cands = board.GetCandidatesForCheck(player);
                // 最大最小选择时，同等价值按优先级排序
                sorted_jj_cands(board, player, cands);
            }
        }
        else
        {
            // 任何时候有杀着时，以其作为唯一候选
            auto last = hist.back();
            // 存在杀时
            if (sha.IsValid())
            {
                if (sha != prohibit_)
                {
                    return {sha};
                }
                else
                {
                    return {};
                }
            }
            else
            {
                // 必须应将
                if (last.is_check())
                {
                    cands = check_response(board, next_player, last);
                }
                else
                {
                    // board.show_board();
                    eats = board.GetCandidatesForEat(next_player, true);
                    // 按目标价值排序【从大到小】
                    std::stable_sort(eats.begin(), eats.end(), [](const Move &lhs, const Move &rhs)
                                     { return get_piece_value(lhs.info.tgt) > get_piece_value(rhs.info.tgt); });

                    // 先手除吃外，另外还有将军
                    if (t % 2 == 0)
                    {
                        auto prev = hist[t - 2];
                        // 非将军后终止
                        if (!prev.is_check())
                        {
                            return {};
                        }
                        // 参考图12-3 应优先车吃。即将军同时吃强子在将军候选中优先
                        auto jjs = get_check_cands(board, player);
                        for (auto m : jjs)
                        {
                            if (get_piece_value(m.info.tgt) == 2 * STRONG_VALUE)
                            {
                                cands.push_back(m);
                            }
                        }
                        // 当可吃车时，优先将军
                        for (auto m : eats)
                        {
                            if (m.info.tgt.piece == PieceType::KING || get_piece_value(m.info.tgt) <= STRONG_VALUE)
                            {
                                continue;
                            }
                            if (contains(init_eats_, m))
                            {
                                continue;
                            }
                            if (!contains(cands, m))
                            {
                                cands.push_back(m);
                            }
                        }
                        for (auto m : jjs)
                        {
                            if (!contains(cands, m))
                            {
                                cands.push_back(m);
                            }
                        }
                        // 排除初始吃后，限定于吃无根子或吃子有价值
                        for (auto m : eats)
                        {
                            if (m.info.tgt.piece == PieceType::KING || get_piece_value(m.info.tgt) < WEAK_VALUE)
                            {
                                continue;
                            }

                            if (contains(init_eats_, m))
                            {
                                continue;
                            }

                            if (!contains(cands, m) && (!board.HasRootProtected(m) || get_piece_value(m.info.src) < get_piece_value(m.info.tgt)))
                            {
                                cands.push_back(m);
                            }
                        }
                    }
                    else
                    {
                        eats = get_sorted_eats(eats, true);
                        for (auto m : eats)
                        {
                            if (m.info.tgt.piece == PieceType::KING || get_piece_value(m.info.tgt) < WEAK_VALUE)
                            {
                                continue;
                            }
                            cands.push_back(m);
                        }
                    }
                }
            }
        }
        if (t % 2 == 0)
        {
            // 针对先行方而言，剔除禁止移动
            cands.erase(std::remove_if(cands.begin(), cands.end(),
                                       [=](const Move &m)
                                       {
                                           return prohibit_ == m;
                                       }),
                        cands.end());
        }
        // 如应早停，候选返回空
        if (should_early_stop(node_ptr, cands, board))
        {
            return {};
        }
        else
        {
            return cands;
        }
        return cands;
    }

    void JdzSimulator::evaluate(std::shared_ptr<Node> &node_ptr, const Board &board)
    {
        // 评估
        float value = 0.0f;
        auto t = node_ptr->depth();
        auto game_result = board.final_result();
        auto expected = player == S_RED ? 1 : -1;
        bool is_draw = game_result == 0;
        auto gain = get_net_gain(node_ptr->history);
        if (game_result == expected)
        {
            if (!node_ptr->history.empty())
            {
                node_ptr->history.back().info.s_score = KING_VALUE;
            }
            node_ptr->s_score = KING_VALUE;
            node_ptr->pass = true;
            gain += KING_VALUE;
        }
        else if (game_result == -expected)
        {
            if (!node_ptr->history.empty())
            {
                node_ptr->history.back().info.s_score = -KING_VALUE;
            }
            node_ptr->s_score = -KING_VALUE;
            node_ptr->stop = true;
            gain -= KING_VALUE;
        }
        else if (is_draw)
        {
            if (!node_ptr->history.empty())
            {
                node_ptr->history.back().info.s_score = -KING_VALUE;
            }
            node_ptr->s_score = -KING_VALUE;
            node_ptr->history.back().info.s_draw = true;
            node_ptr->stop = true;
            gain -= KING_VALUE;
        }
        else
        {
            // if (is_path_dezi(node_ptr->history) && gain >= WEAK_VALUE)
            if (is_path_dezi(node_ptr->history))
            {
                node_ptr->pass = true;
            }
            else if (gain < 0)
            {
                node_ptr->stop = true;
            }
            if (!node_ptr->history.empty())
            {
                node_ptr->history.back().info.s_score = gain;
            }
            node_ptr->s_score = gain;
        }
        // 分母已经同加1
        value = static_cast<float>(gain) / static_cast<float>(base_value);
        node_ptr->value = value * std::pow(value_discout, t - 1);
    }

    std::shared_ptr<Node> JdzSimulator::fixed_node(std::shared_ptr<Node> node_ptr)
    {
        std::shared_ptr<Node> to_cut_node;
        auto fixed = node_ptr;
        fixed = pre_fixed_node(node_ptr);
        // fmt::print("处理 = {}\n", fixed->path());
        // 首先反向，然后正向
        fixed = get_backward_fixed_node(fixed);
        // fmt::print("反向 = {}\n", fixed->path());
        fixed = get_forward_fixed_node(fixed);
        if (node_ptr->history.size() > fixed->history.size())
        {
            auto fixed_t = fixed->history.size();
            to_cut_node = fixed->select_child(node_ptr->history[fixed_t]);
            to_cut_node->cutted_ = true;
            // 清理待处理任务
            remove_tasks(to_cut_node);
        }

        if (node_ptr->history.size() > fixed->history.size())
        {
            auto fixed_t = fixed->history.size();
            auto fixed_gain = get_net_gain(fixed->history);

            // 非叶子节点 --> 叶子节点
            // if (fixed->all_child_cutted())
            {
                // if (is_path_dezi(fixed->history) && fixed_gain >= STRONG_VALUE)
                if (is_path_dezi(fixed->history))
                {
                    fixed->pass = true;
                }
                else if (fixed_gain < 0)
                {
                    fixed->stop = true;
                }
                if (!fixed->history.empty())
                {
                    fixed->history.back().info.s_score = fixed_gain;
                }
                fixed->s_score = fixed_gain;
                fixed->value = static_cast<float>(fixed_gain) / static_cast<float>(base_value) * std::pow(value_discout, fixed_t >= 1 ? fixed_t - 1 : 0);
            }
        }

        // 向上传播
        if (node_ptr->history.size() > fixed->history.size())
        {
            partially_backpropagate(node_ptr, fixed);
        }
        if (!fixed->is_root() && fixed->history.back().info.s_draw)
        {
            backpropagate(fixed->parent);
        }
        else
        {
            // 正常传播叶子节点
            backpropagate(fixed);
        }
        // 裁剪兄弟节点
        auto n = fixed;
        while (n->depth() >= 1)
        {
            // 当节点指示需要裁剪兄弟节点，且本身已经通过时
            if (n->pass && n->cutted_brothers_)
            {
                bool refresh = false;
                for (auto b : n->parent->children)
                {
                    if (n->is_brother(b) && b->visit_count >= 1 && (b->s_score - n->s_score) < STRONG_VALUE)
                    {
                        b->cutted_ = true;
                        refresh = true;
                    }
                }
                if (refresh)
                {
                    backpropagate(n);
                }
            }
            n = n->parent;
        }
        return fixed;
    }
}