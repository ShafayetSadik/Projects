class GeneGame:
    def __init__(self, pool, target, weights):
        self.pool = pool.copy()
        self.target = target
        self.weights = weights[:len(target)]
        self.best_sequence = ""
        self.best_score = float('inf')  # <--- CHANGE THIS LINE

    def calculate_utility(self, gene_sequence, special_nucleotide_pos=None, sid_first_two=None):
        score = 0
        n = max(len(gene_sequence), len(self.target))
        for i in range(n):
            gene_ascii = ord(gene_sequence[i]) if i < len(gene_sequence) else 0
            target_ascii = ord(self.target[i]) if i < len(self.target) else 0
            weight = self.weights[i] if i < len(self.weights) else 1
            if special_nucleotide_pos is not None and i >= special_nucleotide_pos and sid_first_two:
                weight *= sid_first_two / 100
            score -= weight * abs(gene_ascii - target_ascii)
        return score

    def alphabeta(self, gene_sequence, pool, depth, alpha, beta, maximizing_player, 
                  special_nucleotide_pos=None, sid_first_two=None):
        if len(pool) == 0:
            score = self.calculate_utility(gene_sequence, special_nucleotide_pos, sid_first_two)
            # Always update best_score and best_sequence at leaf nodes
            if score < self.best_score:  # <--- CHANGE THIS LINE
                self.best_score = score
                self.best_sequence = gene_sequence
            return score
        if maximizing_player:
            min_eval = float('inf')
            for i, nucleotide in enumerate(pool):
                new_pool = pool[:i] + pool[i+1:]
                new_sequence = gene_sequence + nucleotide
                new_special_pos = len(gene_sequence) if nucleotide == 'S' else special_nucleotide_pos
                eval = self.alphabeta(new_sequence, new_pool, depth-1, alpha, beta, False, 
                                      new_special_pos, sid_first_two)
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    break
            return min_eval
        else:
            min_eval = float('inf')
            for i, nucleotide in enumerate(pool):
                new_pool = pool[:i] + pool[i+1:]
                new_sequence = gene_sequence + nucleotide
                eval = self.alphabeta(new_sequence, new_pool, depth-1, alpha, beta, True,
                                      special_nucleotide_pos, sid_first_two)
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    break
            return min_eval

def solve_task1():
    pool = input().split(',')
    target = input()
    sid = input().split()
    weights = [int(x) for x in sid][-len(target):]
    game = GeneGame(pool, target, weights)
    game.alphabeta("", pool, len(pool), float('-inf'), float('inf'), True)
    print(f"Best gene sequence generated: {game.best_sequence}")
    print(f"Utility score: {game.best_score}")

def solve_task2():
    pool = input().split(',')
    target = input()
    sid = input().split()
    weights = [int(x) for x in sid][-len(target):]
    pool = [x.strip() for x in pool]
    pool.append('S')
    sid_first_two = float(str(sid[0]) + str(sid[1]))
    game = GeneGame(pool, target, weights)
    game.alphabeta("", pool, len(pool), float('-inf'), float('inf'), True, None, sid_first_two)
    game_without_s = GeneGame(pool[:-1], target, weights)
    game_without_s.alphabeta("", pool[:-1], len(pool)-1, float('-inf'), float('inf'), True)
    print("YES" if game.best_score > game_without_s.best_score else "NO")
    print("With special nucleotide")
    print(f"Best gene sequence generated: {game.best_sequence}")
    print(f"Utility score: {game.best_score:.2f}")

# Uncomment the task you want to run
solve_task1()
#solve_task2()