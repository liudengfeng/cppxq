#include "Pybind.hpp"

void registerPy(pybind11::module &m)
{
    namespace py = pybind11;
    m.doc() = "C++中国象棋包";
    py::class_<Piece>(m, "Piece")
        .def_readonly("x", &Piece::x)
        .def_readonly("y", &Piece::y)
        .def_readonly("color_id", &Piece::color_id)
        .def_readonly("piece_id", &Piece::piece_id)
        .def_readonly("color_name", &Piece::color_name)
        .def_readonly("piece_name", &Piece::piece_name);

    py::class_<XqBoard>(m, "XqBoard")
        .def(py::init<>())
        .def("reset", &XqBoard::reset, "重置棋盘")
        .def("clone", &XqBoard::clone, "复制棋盘")
        .def("back_one_step", &XqBoard::undoMove, "回退一步")
        .def("get_fen", &XqBoard::get_fen_string, py::arg("include_moves") = false, py::arg("simple") = false, py::arg("include_no_eat") = true)
        .def("get_piece", &XqBoard::get_piece, "指定坐标位置棋子对象")
        .def("get_pieces", &XqBoard::get_pieces, py::arg("lr") = false, "棋盘棋子对象列表")
        .def("piece_cn_names", &XqBoard::piece_cn_names, "棋子中文名称列表")
        .def("piece_cn_colors", &XqBoard::piece_cn_colors, "棋子中文颜色列表")
        .def("next_player_string", &XqBoard::next_player_string, "下一步走子方中文字符串")
        .def("game_result_string", &XqBoard::game_result_string, "游戏结果字符串")
        .def("init_set", py::overload_cast<std::string, bool, bool>(&XqBoard::set_pieces), py::arg("str"), py::arg("verify") = true, py::arg("include_no_eat") = false, "初始化棋盘设置")
        .def("set_use_rule_flag", &XqBoard::set_use_rule_flag, "设置是否进行18步检测")
        .def("set_result", &XqBoard::SetResult, py::arg("int"), py::arg("reason") = "非法走子", "设定棋局结果")
        // .def("set_pieces_by_2d", &XqBoard::set_pieces_by_2d, py::arg("data"), py::arg("to_play") = 1, py::arg("steps") = 1, py::arg("continuous_uneaten") = 0, "使用棋子编号设置棋盘")
        // .def("set_pieces_by_list", &XqBoard::set_pieces_by_list, py::arg("data"), py::arg("to_play") = 1, py::arg("steps") = 1, py::arg("continuous_uneaten") = 0, "使用棋子编号设置棋盘")
        .def("set_player", py::overload_cast<std::string>(&XqBoard::SetPlayer), "初始下一步走子方")
        .def("steps", &XqBoard::steps)
        .def("no_eat", &XqBoard::no_eat, "连续未吃子数量")
        .def("move", py::overload_cast<int>(&XqBoard::step), "整数编码移动")
        .def("do_move_str", py::overload_cast<std::string>(&XqBoard::step), "执行字符串表示的移动")
        .def("do_move_coord", py::overload_cast<int, int, int, int>(&XqBoard::step), "执行坐标表示的移动")
        .def("next_player", &XqBoard::int_next_player, "整数形式表达的下一步走子方")
        .def("legal_actions", &XqBoard::legal_ations, "下一步走子方排除自杀移动后，以整数形式表达的移动列表")
        .def("eat_actions", &XqBoard::eat_actions, "下一步走子方排除自杀移动后，以整数形式表达的吃子移动列表")
        .def("flipup", &XqBoard::flipup, "红黑棋子互换的棋盘")
        .def("fliplr", &XqBoard::fliplr, "棋子位置左右互换的棋盘")
        .def("get_rb_fen", &XqBoard::get_rb_fen, "红黑棋子互换后的fen字符串")
        .def("get_lr_fen", &XqBoard::get_lr_fen, "棋子位置左右互换后的fen字符串")
        .def("get_piece_id", &XqBoard::get_piece_id, "获取坐标轴上棋子对应的编码")
        .def("get_piece_bid", &XqBoard::get_piece_bid, "获取坐标轴上棋子对应棋盘数组序号编码")
        .def("get2d", &XqBoard::get2d, py::arg("lr") = false, "二维棋盘棋子数字表达")
        .def("get3d", &XqBoard::get3d, py::arg("lr") = false, "三维棋盘棋子数字表达")
        .def("get_action_feature", &XqBoard::getActionFeature, "移动前移动编码特征")
        .def("repetition_size", &XqBoard::repetition_size)
        .def("is_multi_repetitive", &XqBoard::is_multi_repetitive)
        .def("is_finished", &XqBoard::is_game_ended)
        .def("reward", &XqBoard::final_result)
        .def("get_board_view_string", &XqBoard::board_view_string, py::arg("viewDetail") = false, py::arg("title") = "比赛", "棋盘显示字符串")
        .def("show_board",
             &XqBoard::show_board,
             py::arg("viewDetail") = false,
             py::arg("title") = "比赛",
             py::call_guard<py::scoped_ostream_redirect,
                            py::scoped_estream_redirect>());

    m.def("movestr2action", &str2action, "移动字符串转换为其映射序号")
        .def("action2movestr", &action2str, "将映射序号转换为代表移动的4位数字符串")
        .def("move2lr", &move2lr, "移动左右位置互换后的4位数字符串");
}
