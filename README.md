# Pixelated
→ Report on the Spell Master Game
    → Introduction

The provided C program implements a game called Spell Master, where players engage in a wizard battle by taking turns casting spells. The game involves strategic spell selection based on certain rules, creating an engaging player-vs-bot experience.



→ Game Overview

    → Spells and Spell Selection:
        Players are provided with a list of spells from which they can choose.
        Spells can only be chosen once (repetitions are not allowed).
        Every chosen spell, except the first, must start with the same character as the last character of the previously chosen spell.
    → Winning Conditions:
        A player wins if the opponent fails to cast a spell satisfying the following conditions:
            The opponent casts a spell not in the provided list.
            The opponent chooses a spell that has already been cast during the battle.
            The opponent selects a spell whose first character does not match the last character of the previously chosen spell.
            The opponent runs out of spells that satisfy the matching characters condition.
    → Game Termination:
        The game ends when one of the players wins, meeting the conditions outlined above.

→ Strategy Overview
    The game employs a combination of random selection and strategic decision-making, primarily implemented in the bot's move generation. The bot aims to choose spells strategically based on the last character of the previous spell, while also considering potential blocking spells to create a challenging gameplay experience.



→ Bot's Move Generation
    → The bot's move generation strategy is as follows:
        Game Tree Representation:

        -   Random First Move: 
        In the first move, the bot randomly selects a spell from the list to initiate the game.

        -   Minimax Algorithm: 
        For subsequent moves, the bot uses the minimax algorithm to evaluate potential moves. The algorithm explores possible moves by considering the impact of each move on the future state of the game. The minimax function in our program is a recursive function that explores the game tree by considering different moves and their outcomes. The recursion depth corresponds to the depth of the search in the tree. Nodes in the game tree would correspond to different game states, and edges would represent possible moves between states. In the code, these are not explicitly stored in a tree structure but are rather simulated during the recursive execution of the minimax function.

        -   Alpha-Beta Pruning: 
        The minimax algorithm incorporates alpha-beta pruning, optimizing the search space by eliminating branches that cannot lead to a better outcome. Alpha-beta pruning is applied in the minimax function to eliminate branches of the search tree that cannot influence the final decision. This helps reduce the number of nodes that need to be evaluated.
        While the actual tree structure is not explicitly constructed in memory, the algorithm follows the principles of the minimax algorithm, navigating through possible moves and their consequences in a way that aligns with the concept of a game tree.

        -   Risk Evaluation: 
        The bot evaluates the risk associated with each potential move. It checks for spells that could potentially block its own subsequent moves and adjusts its strategy accordingly.

        -   Strategic Decision-Making: 
        The bot prioritizes moves that maximize its chances of winning while avoiding risky situations. It aims to make optimal decisions based on the current state of the game. The evaluateMove function in your program serves as the evaluation function for the leaf nodes, determining the score of a particular move based on certain criteria.



→ Conclusion
    The Spell Master game provides an engaging experience by combining strategic decision-making with an element of randomness. The bot's move generation strategy, involving the minimax algorithm and risk evaluation, enhances the complexity of the game and challenges players to think strategically to outsmart their magical opponent. The game's adherence to well-defined rules ensures fair gameplay and an enjoyable wizard battle.