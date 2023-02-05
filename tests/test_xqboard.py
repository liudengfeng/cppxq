import xqcpp
import pytest


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
