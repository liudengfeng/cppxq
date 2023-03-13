import xqcpp
import pytest
import numpy as np


@pytest.mark.parametrize(
    "init_fen,expected",
    [
        (
            "3ak1NrC/9/4b4/9/2n1c1P2/9/3R5/9/2p6/2BK1A3 r - 0 0 1",
            "CrN1ka3/9/4b4/9/2P1c1n2/9/5R3/9/6p2/3A1KB2 r - 0 0 1",
        )
    ],
)
def test_lr_fen(init_fen, expected):
    board = xqcpp.XqBoard()
    board.init_set(init_fen, True)
    actual = board.get_lr_fen()
    # print(actual)
    assert expected == actual


@pytest.mark.parametrize(
    "init_fen,expected",
    [
        (
            "3ak1NrC/9/4b4/9/2n1c1P2/9/3R5/9/2p6/2BK1A3 r - - 0 1",
            # 红方在上、黑方在下，方便按`0001`移动格式取值
            [
                [0, 0, 3, 7, 0, 2, 0, 0, 0],
                [0, 0, -1, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 6, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, -5, 0, -4, 0, 1, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, -3, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, -2, -7, 0, 5, -6, 4],
            ],
        )
    ],
)
def test_2d(init_fen, expected):
    board = xqcpp.XqBoard()
    board.init_set(init_fen, True)
    actual = board.get2d()
    # print(actual)
    assert expected == actual


# def test_set_by_list():
#     data = np.array(
#         [
#             [0, 0, 3, 7, 0, 2, 0, 0, 0],
#             [0, 0, -1, 0, 0, 0, 0, 0, 0],
#             [0, 0, 0, 0, 0, 0, 0, 0, 0],
#             [0, 0, 0, 6, 0, 0, 0, 0, 0],
#             [0, 0, 0, 0, 0, 0, 0, 0, 0],
#             [0, 0, -5, 0, -4, 0, 1, 0, 0],
#             [0, 0, 0, 0, 0, 0, 0, 0, 0],
#             [0, 0, 0, 0, -3, 0, 0, 0, 0],
#             [0, 0, 0, 0, 0, 0, 0, 0, 0],
#             [0, 0, 0, -2, -7, 0, 5, -6, 4],
#         ]
#     )
#     pieces = data.flatten().tolist()
#     assert len(pieces) == 90
#     board = xqcpp.XqBoard()
#     board.set_pieces_by_2d(pieces, 1, 1, 0)
#     board.show_board()
#     print(board.get_fen())
#     # assert board.get_fen() == "3ak1NrC/9/4b4/9/2n1c1P2/9/3R5/9/2p6/2BK1A3 r - - 0 1"


@pytest.mark.parametrize(
    "init_fen,lr_fen",
    [
        (
            "3ak1NrC/9/4b4/9/2n1c1P2/9/3R5/9/2p6/2BK1A3 r - 0 0 1",
            "CrN1ka3/9/4b4/9/2P1c1n2/9/5R3/9/6p2/3A1KB2 r - 0 0 1",
        )
    ],
)
def test_lr_fen_2d(init_fen, lr_fen):
    board = xqcpp.XqBoard()
    board.init_set(init_fen, True)
    actual = board.get2d(True)
    b2 = xqcpp.XqBoard()
    b2.init_set(lr_fen, True)
    data = b2.get2d()
    np.testing.assert_array_equal(data, actual)

    lr_data = b2.get2d(True)
    np.testing.assert_array_equal(np.fliplr(data), lr_data)


@pytest.mark.parametrize(
    "init_fen,moves,expected",
    [
        (
            "3ak1NrC/4a4/4b4/9/9/9/9/9/2p1r4/3K5 r - 110 0 1",
            ["8988", "7978"],
            112,
        ),
        (
            "3ak1NrC/4a4/4b4/9/9/9/9/9/2p1r4/3K5 r - 110 0 1",
            ["6948"],
            0,
        ),
        (
            "3ak1NrC/4a4/4b4/9/9/9/9/9/2p1r4/3K5 r - 110 0 1",
            ["6948", "4948", "8988"],
            1,
        ),
    ],
)
def test_no_eat(init_fen, moves, expected):
    board = xqcpp.XqBoard()
    board.init_set(init_fen, True)
    for move in moves:
        board.do_move_str(move)
    assert board.no_eat() == expected


def test_steps():
    init_fen = "3ak1NrC/4a4/4b4/9/9/9/9/9/2p1r4/3K5 r - 118 149 298"
    board = xqcpp.XqBoard()
    board.init_set(init_fen, True)
    board.show_board()
    assert board.steps() == 298
