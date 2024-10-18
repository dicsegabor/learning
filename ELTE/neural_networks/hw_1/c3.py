import unittest
import numpy as np

class SudokuBoard:
    def __init__(self) -> None:
        self.board = np.zeros(81, dtype=np.int32).reshape(9,9)

    # view only
    def get_blocks(self, row_n = 3, col_n = 3):
        return (self.board.reshape(self.board.shape[1]//row_n, row_n, -1, col_n)
               .swapaxes(1,2)
               .reshape(-1, row_n * col_n)) 
    
    def get_block(self, row_idx, col_idx) -> np.ndarray((3,3)):
        bl_row = (np.floor(row_idx / 3) * 3).astype(int)
        bl_col = (np.floor(col_idx / 3) * 3).astype(int)
        return self.board[bl_row : bl_row + 3, 
                          bl_col : bl_col + 3]

    def can_place(self, row_idx, col_idx, num) -> bool:
        empty = self.board[row_idx, col_idx] == 0
        row = not np.isin(num, self.board[row_idx,:])
        column = not np.isin(num, self.board[:, col_idx])
        block = not np.isin(num, self.get_block(row_idx, col_idx)) 

        return empty and row and column and block

    def place(self, row_idx, col_idx, num) -> bool:
        if self.can_place(row_idx, col_idx, num):
            self.board[row_idx, col_idx] = num
            return True

        return False

    def get_num_empty_blocks(self) -> int:
        blocks = self.get_blocks()
        empty_blocks = np.where((blocks == 0).all(axis=1))[0]
        return empty_blocks.size

    def get_row_idxs_with_missing_num(self, num) -> np.ndarray:
        return np.where((num != self.board).all(axis=1))[0]

    def get_col_idx_with_minimal_max(self) -> int or None:
        col_maxes = np.amax(self.board, axis=0)

        valid_idx = np.where(col_maxes > 0)[0]
        if valid_idx.size == 0:
            return None
        return valid_idx[col_maxes[valid_idx].argmin()]

    def get_num_blocks_with_two_nums_present(self, num1, num2) -> int:
        blocks = self.get_blocks()
        mask_num1 = (blocks == num1).any(axis=1)
        mask_num2 = (blocks[mask_num1,:] == num2).any(axis=1)
        return np.sum(mask_num2)

class TestSudoku(unittest.TestCase):
    def test_can_place(self):
        sb = SudokuBoard()
        self.assertTrue(sb.can_place(0, 0, 5))
        self.assertTrue(sb.can_place(8, 0, 5))
        self.assertTrue(sb.can_place(0, 8, 5))
        self.assertTrue(sb.can_place(4, 6, 5))
        self.assertTrue(sb.can_place(8, 8, 5))

        sb.place(3, 3, 5)
        self.assertFalse(sb.can_place(3, 3, 7))
        self.assertFalse(sb.can_place(5, 4, 5))
        self.assertFalse(sb.can_place(7, 3, 5))
        self.assertFalse(sb.can_place(3, 7, 5))
        
        self.assertTrue(sb.can_place(2, 4, 5))
        self.assertTrue(sb.can_place(3, 4, 6))

    def test_place(self):
        sb = SudokuBoard()
        self.assertTrue(sb.place(2, 7, 4))
        self.assertFalse(sb.place(2, 7, 4))
        self.assertFalse(sb.place(2, 7, 5))
        self.assertTrue(sb.place(2, 0, 5))
        self.assertFalse(sb.place(2, 8, 5))

    def test_get_num_empty_blocks(self):
        sb = SudokuBoard()
        self.assertEqual(sb.get_num_empty_blocks(), 9)
        sb.place(3, 3, 9)
        self.assertEqual(sb.get_num_empty_blocks(), 8)
        
        to_insert = [(1, 0, 3), (2, 7, 3), (2, 1, 4)]
        [sb.place(*t) for t in to_insert]
        self.assertEqual(sb.get_num_empty_blocks(), 6)
        to_insert = [(5, 8, 4), (8, 0, 4), (3, 7, 8)]
        [sb.place(*t) for t in to_insert]
        self.assertEqual(sb.get_num_empty_blocks(), 4)

    def test_get_row_idxs_with_missing_num(self):
        sb = SudokuBoard()
        ret = sb.get_row_idxs_with_missing_num(1)
        self.assertEqual(ret.shape, (9,))
        self.assertEqual(tuple(np.sort(ret)), tuple(range(9)))

        to_insert = [(1, 0, 3), (2, 7, 3), (2, 1, 4), (5, 8, 4), (8, 0, 4), (3, 7, 8)]
        [sb.place(*t) for t in to_insert]
        ret = sb.get_row_idxs_with_missing_num(1)
        self.assertEqual(ret.shape, (9,))
        self.assertEqual(tuple(np.sort(ret)), tuple(range(9)))
        ret = sb.get_row_idxs_with_missing_num(4)
        self.assertEqual(ret.shape, (6,))
        self.assertEqual(tuple(np.sort(ret)), (0,1,3,4,6,7))

        to_insert = [(4, 2, 4), (1, 4, 4), (3, 3, 4), (0, 6, 4), (6, 7, 4)]
        [sb.place(*t) for t in to_insert]
        ret = sb.get_row_idxs_with_missing_num(4)
        self.assertEqual(ret.shape, (1,))
        self.assertEqual(tuple(ret), (7,))

        sb.place(7, 5, 4)
        ret = sb.get_row_idxs_with_missing_num(4)
        self.assertEqual(ret.shape, (0,))

    def test_get_col_idx_with_minimal_max(self):
        sb = SudokuBoard()
        self.assertEqual(sb.get_col_idx_with_minimal_max(), None)
        sb.place(3, 3, 9)
        self.assertEqual(sb.get_col_idx_with_minimal_max(), 3)
        
        to_insert = [(1, 0, 3), (2, 7, 3)]
        [sb.place(*t) for t in to_insert]
        self.assertIn(sb.get_col_idx_with_minimal_max(), [0, 7])

        sb.place(2, 0, 4)
        self.assertEqual(sb.get_col_idx_with_minimal_max(), 7)

        to_insert = [(8, 3, 1), (8, 1, 2), (3, 7, 8)]
        [sb.place(*t) for t in to_insert]
        self.assertEqual(sb.get_col_idx_with_minimal_max(), 1)

    def test_get_num_blocks_with_two_nums_present(self):
        sb = SudokuBoard()
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(5, 7), 0)
        sb.place(3, 3, 9)
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(9, 1), 0)
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(9, 8), 0)
        sb.place(5, 3, 5)
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(9, 5), 1)
        
        to_insert = [(3, 8, 5), (5, 2, 9), (6, 2, 5), (6, 3, 1)]
        [sb.place(*t) for t in to_insert]
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(5, 9), 1)
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(9, 5), 1)
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(9, 1), 0)
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(5, 1), 0)

        to_insert = [(6, 7, 9), (7, 4, 9), (0, 2, 2), (0, 7, 5), (5, 0, 3), (8, 5, 3)]
        [sb.place(*t) for t in to_insert]
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(5, 9), 1)
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(9, 3), 2)
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(5, 2), 0)
        self.assertEqual(sb.get_num_blocks_with_two_nums_present(3, 1), 1)

def suite():
    suite = unittest.TestSuite()
    testfuns = ["test_can_place", "test_place", "test_get_num_empty_blocks",
                "test_get_row_idxs_with_missing_num", "test_get_col_idx_with_minimal_max",
                "test_get_num_blocks_with_two_nums_present"]
    [suite.addTest(TestSudoku(fun)) for fun in testfuns]
    return suite

runner = unittest.TextTestRunner(verbosity=2)
runner.run(suite())
