class GeneSequenceGame:
    def __init__(self, pool, target, student_id):
        self.pool = list(pool)
        self.target = target
        self.student_id = student_id
        self.weights = self.get_weights()
        self.has_special = 'S' in self.pool
        
    def get_weights(self):
        sid_str = str(self.student_id)
        n = len(self.target)
        if len(sid_str) >= n:
            return [int(d) for d in sid_str[-n:]]
        else:
            return [0] * (n - len(sid_str)) + [int(d) for d in sid_str]
    
    def calculate_utility(self, gene_sequence, s_position=None):      
        n = max(len(gene_sequence), len(self.target))
        weights = self.weights.copy()
        
        if s_position is not None:
            multiplier = int(str(self.student_id)[:2]) / 100 if len(str(self.student_id)) >= 2 else 0.01
            for i in range(s_position, len(weights)):
                weights[i] *= multiplier
        
        total_score = 0
        for i in range(n):
            weight = weights[i] if i < len(weights) else 1  # default weight
            gene_char = ord(gene_sequence[i]) if i < len(gene_sequence) else 0
            target_char = ord(self.target[i]) if i < len(self.target) else 0
            total_score += weight * abs(gene_char - target_char)
        
        return -total_score
    
    def minimax(self, pool, gene_sequence, is_maximizing, alpha, beta, depth=0, s_position=None):
        """Minimax algorithm with alpha-beta pruning"""
        if not pool:  # Terminal state
            return self.calculate_utility(gene_sequence, s_position), gene_sequence
        
        if is_maximizing:  # Agent 1 (Maximizer)
            max_eval = float('-inf')
            best_sequence = ""
            
            for nucleotide in pool:
                new_pool = pool.copy()
                new_pool.remove(nucleotide)
                new_sequence = gene_sequence + nucleotide
                
                new_s_position = s_position
                if nucleotide == 'S' and s_position is None:
                    new_s_position = len(gene_sequence)
                
                eval_score, rest_sequence = self.minimax(new_pool, new_sequence, False, alpha, beta, depth + 1, new_s_position)
                
                if eval_score > max_eval:
                    max_eval = eval_score
                    best_sequence = rest_sequence
                
                alpha = max(alpha, eval_score)
                if beta <= alpha:
                    break  # Alpha-beta pruning
            
            return max_eval, best_sequence
        
        else:  # Agent 2 (Minimizer)
            min_eval = float('inf')
            best_sequence = ""
            
            for nucleotide in pool:
                new_pool = pool.copy()
                new_pool.remove(nucleotide)
                new_sequence = gene_sequence + nucleotide
                
                # Agent 2 doesn't activate special nucleotide, so s_position remains unchanged
                eval_score, rest_sequence = self.minimax(new_pool, new_sequence, True, alpha, beta, depth + 1, s_position)
                
                if eval_score < min_eval:
                    min_eval = eval_score
                    best_sequence = rest_sequence
                
                beta = min(beta, eval_score)
                if beta <= alpha:
                    break  # Alpha-beta pruning
            
            return min_eval, best_sequence
    
    def solve_task1(self):
        pool_without_s = [n for n in self.pool if n != 'S']
        score, sequence = self.minimax(pool_without_s, "", True, float('-inf'), float('inf'))
        return sequence, score
    
    def solve_task2(self):
        if not self.has_special:
            return self.solve_task1()
 
        without_s_sequence, without_s_score = self.solve_task1()

        with_s_score, with_s_sequence = self.minimax(self.pool, "", True, float('-inf'), float('inf'))
        
        use_special = with_s_score > without_s_score
        
        return {
            'use_special': "YES" if use_special else "NO",
            'without_s': (without_s_sequence, without_s_score),
            'with_s': (with_s_sequence, with_s_score),
            'recommendation': use_special
        }


def main():
    try:
        pool_input = input("Enter nucleotides pool (comma-separated, e.g., A,T,C,G): ").strip()
        pool = [nucleotide.strip() for nucleotide in pool_input.split(',')]

        target = input("Enter target gene sequence (e.g., ATGC): ").strip().upper()

        student_id_input = input("Enter student ID (space-separated digits, e.g., 1 8 1 0 4 0 5 2): ").strip()
        student_id = int(''.join(student_id_input.split()))

        print(f"\nInput received:")
        print(f"Pool: {pool}")
        print(f"Target: {target}")
        print(f"Student ID: {student_id}")
    
        #which task to solve
        task_choice = input("Which task do you want to solve? Enter 1 for Task I or 2 for Task II: ").strip()
        if task_choice not in ['1', '2']:
            print("Invalid choice. Please enter 1 or 2.")
            return

    except ValueError as e:
        print(f"Error in input format: {e}")
        return
    except Exception as e:
        print(f"Error: {e}")
        return

    # For Task II, automatically add 'S' to the pool if not present
    if task_choice == '2' and 'S' not in pool:
        pool.append('S')

    game = GeneSequenceGame(pool, target, student_id)

    if task_choice == '1':
        print("\n Task I Solution (Basic Minimax)")
        sequence, score = game.solve_task1()
        print(f"Best gene sequence generated: {sequence}")
        print(f"Utility score: {score}")
    else:
        print("\nTask II Solution (With Special Nucleotide)")
        result = game.solve_task2()
        print(f"Decision: {result['use_special']}")
        print(f"With special nucleotide:")
        print(f"  Sequence: {result['with_s'][0]}")
        print(f"  Score: {result['with_s'][1]:.2f}")

 #       if result['recommendation']:
 #           print("Recommendation: Use the special nucleotide 'S' for better utility.")
 #       else:
 #           print("Recommendation: Do not use the special nucleotide 'S'.")

if __name__ == "__main__":
    main()