import random

choices = ['rock', 'paper', 'scissors']

player = input("Choose rock, paper, or scissors: ")
computer = random.choice(choices)

print(f"Computer chose: {computer}")

if player == computer:
    print("Tie!")
elif player == "rock" and computer == "scissors":
    print("You win!")
elif player == "paper" and computer == "rock":
    print("You win!")
elif player == "scissors" and computer == "paper":
    print("You win!")
else:
    print("Computer wins!")
