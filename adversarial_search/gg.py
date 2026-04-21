# Function to calculate the utility score based on the gene sequence and target
def calculate_utility(gene_sequence, target_sequence, weights, SID):
    score = 0
    for i in range(len(gene_sequence)):
        # Get ASCII values of gene and target at position i
        gene_ascii = ord(gene_sequence[i]) if i < len(gene_sequence) else 0
        target_ascii = ord(target_sequence[i]) if i < len(target_sequence) else 0
        # Get weight for the position, default to 1 if not provided
        weight = weights[i] if i < len(weights) else 1
        # Calculate score
        score += weight * abs(gene_ascii - target_ascii)
    return -score

# Minimax algorithm with alpha-beta pruning
def minimax(remaining_pool, current_gene_sequence, target_sequence, is_agent1_turn, alpha, beta, weights, SID, depth=0):
    if depth == len(target_sequence):  # If depth reaches the target sequence length
        return calculate_utility(current_gene_sequence, target_sequence, weights, SID), current_gene_sequence

    best_gene_sequence = ""
    if is_agent1_turn:  # Maximizer's turn (Agent 1)
        max_utility = -float('inf')
        for nucleotide in remaining_pool:
            new_pool = remaining_pool.copy()
            new_pool.remove(nucleotide)
            new_gene_sequence = current_gene_sequence + nucleotide
            utility, gene_sequence = minimax(new_pool, new_gene_sequence, target_sequence, False, alpha, beta, weights, SID, depth + 1)
            if utility > max_utility:
                max_utility = utility
                best_gene_sequence = gene_sequence
            alpha = max(alpha, max_utility)
            if beta <= alpha:
                break
        return max_utility, best_gene_sequence
    else:  # Minimizer's turn (Agent 2)
        min_utility = float('inf')
        for nucleotide in remaining_pool:
            new_pool = remaining_pool.copy()
            new_pool.remove(nucleotide)
            new_gene_sequence = current_gene_sequence + nucleotide
            utility, gene_sequence = minimax(new_pool, new_gene_sequence, target_sequence, True, alpha, beta, weights, SID, depth + 1)
            if utility < min_utility:
                min_utility = utility
                best_gene_sequence = gene_sequence
            beta = min(beta, min_utility)
            if beta <= alpha:
                break
        return min_utility, best_gene_sequence

# Function to check if selecting special nucleotide 'S' improves the score
def with_special_nucleotide(remaining_pool, target_sequence, SID, weights):
    if 'S' in remaining_pool:
        remaining_pool.remove('S')
        # Find position where 'S' would be placed (since it's always at the last position)
        booster_position = len(target_sequence)  # 'S' is selected at the last position
        booster_factor = float(str(SID)[:2]) / 100  # First two digits of SID divided by 100

        # Adjust weights based on 'S' position
        adjusted_weights = weights.copy()
        for i in range(booster_position, len(adjusted_weights)):
            adjusted_weights[i] *= booster_factor  # Apply the genetic booster multiplier

        # Run minimax to find the best gene sequence with special nucleotide 'S'
        utility, gene_sequence = minimax(remaining_pool, 'S', target_sequence, True, -float('inf'), float('inf'), adjusted_weights, SID)
        return utility, gene_sequence
    return None, None  # Return None if 'S' is not in the pool

# Main function to generate the best gene sequence
def generate_gene_sequence(pool, target, SID):
    remaining_pool = pool.split(',')
    target_sequence = target.strip()
    SID_digits = list(map(int, str(SID)))
    
    # Calculate the initial weights based on SID (last n digits)
    weights = [float(SID_digits[i % len(SID_digits)]) / 100 for i in range(len(target_sequence))]
    
    # Task I: Generate the best gene sequence without using 'S'
    utility, best_gene_sequence = minimax(remaining_pool, "", target_sequence, True, -float('inf'), float('inf'), weights, SID)
    
    # Task II: Check if using 'S' improves the utility score
    special_nucleotide_utility, special_nucleotide_sequence = with_special_nucleotide(remaining_pool, target_sequence, SID, weights)
    
    # Output the results
    if special_nucleotide_utility is not None:
        if special_nucleotide_utility < utility:
            print("YES")
            print("With special nucleotide")
            print(f"Best gene sequence generated: {special_nucleotide_sequence}")
            print(f"Utility score: {special_nucleotide_utility}")
        else:
            print("NO")
            print("With special nucleotide")
            print(f"Best gene sequence generated: {best_gene_sequence}")
            print(f"Utility score: {utility}")
    else:
        print("NO")
        print("With special nucleotide")
        print(f"Best gene sequence generated: {best_gene_sequence}")
        print(f"Utility score: {utility}")

# Sample Input
pool = "A,T,C,G"
target = "ATGC"
SID = "1810452"

# Call the main function with inputs
generate_gene_sequence(pool, target, SID)
