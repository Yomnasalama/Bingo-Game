import random
from random import seed
from random import randint
N = 5
n_players = 2
marks = ['H', 'Y']
elements = ["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25"]
bingo = "BINGO"
hgrid = [["0" for i in range(N)] for j  in range(N)]
ygrid = [["0" for i in range(N)] for j  in range(N)]
hscore = 0
yscore = 0
chosen_elements =  ["0"] * (N*N)
def clear_grid():
  for i in range(N):
    for j in range (N):
      hgrid[i][j] = "0"
      ygrid[i][j] = "0"
def set_elements():
  x = 0
  for k in range(N):
    for l in range(N):
      while hgrid[k][l] == '0':
        i = random.randint(0, 4)
        j = random.randint(0, 4)
        if hgrid[i][j] == "0":
          hgrid[i][j] = elements[x]
          x+=1
  x = 0
  for k in range(N):
    for l in range(N):
      while ygrid[k][l] == '0':
        i = random.randint(0, 4)
        j = random.randint(0, 4)
        if ygrid[i][j] == "0":
          ygrid[i][j] = elements[x]
          x+=1
def check_valid_element(element):
  num = int(element)
  if num < 1 or num > 25:
      return False
  for i in range (N):
        if element  == chosen_elements[i]:
            return False
  return True
def check_win_tie():
    count_row = 0; count_column = 0; count_diagonal = 0; count_reverse = 0; global yscore
    global hscore
    hscore = 0; yscore = 0
    for i in range(N):
        for j in range(N):
            if ygrid[i][j] == "B":
                count_row+=1
            if ygrid[j][i] == "B":
                 count_column +=1
            if i == j:
                if ygrid[i][j] == "B":
                    count_diagonal +=1
            if i+j == 4:
                if ygrid[i][j] == "B" :
                    count_reverse +=1
        if count_column == N :
            yscore +=1
        if count_row == N:
            yscore +=1
        count_row = 0
        count_column = 0
    if count_reverse == N:
        yscore +=1
    if count_diagonal == N:
        yscore +=1
    count_row = 0; count_column = 0; count_diagonal = 0; count_reverse = 0;
    for i in range(N):
        for j in range(N):
            if hgrid[i][j] == "B":
                count_row +=1
            if hgrid[j][i] == "B":
                 count_column +=1
            if i == j:
                if hgrid[i][j] == "B":
                    count_diagonal +=1
            if i+j == 4:
                if hgrid[i][j] == "B":
                    count_reverse +=1
        if count_column == N:
            hscore +=1
        if count_row == N:
            hscore +=1
        count_row = 0
        count_column = 0
    if count_reverse == N:
        hscore +=1
    if count_diagonal == N:
        hscore +=1
    if yscore > hscore and yscore >= N:
        print_grid(ygrid)
        print(" %c Winner winner chicken dinner" %marks[1])
        return True
    elif yscore < hscore and  hscore >= N:
        print_grid(hgrid)
        print(" %c Winner winner chicken dinner" %marks[0])
        return True
    elif yscore == hscore and hscore == N:
        print_grid(ygrid)
        print_grid(hgrid)
        print("TIE!!")
        return True
    return False
def print_grid(grid):
    print('--' + '------' * (N-1))
    print("Player 1: %c  vs  Player 2: %c" % (marks[0], marks[1]))
    print('--' + '---' * (N+6) + '--')
    for i in range(N):
        for j in range(N):
            print(end='|  ')
            if(grid[i][j] != 'B'):
              if int(grid[i][j]) < 10:
                print('  '+grid[i][j], end=' ')
              else:
                print(' '+grid[i][j], end=' ')
            else:
              print('  '+grid[i][j],end = ' ')
        print(end='|')
        print()
        print('--' + '---' * (N+6)+ '--')
    if grid == hgrid:
      for i in range(hscore):
        print('     '+bingo[i],end = ' ')
    else:
      for i in range(yscore):
        print('     '+bingo[i],end = ' ')
    print()
def mark(element):
    for i in range(N):
        for j in range(N):
            if hgrid[i][j] == element:
                hgrid[i][j] = "B"
            if ygrid[i][j] == element:
                ygrid[i][j] = "B"
    for i in range(25):
      if chosen_elements[i] == '0':
        chosen_elements[i] = element
def read_input():
    print("Enter a Number: ",end = ' ')
    i = str(input())
    while not check_valid_element(i):
        print("Enter a valid Number: ",end= ' ')
        i = str(input())
    return i
def play():
        print("Bingo Game...")
        print("-------------------------")
        player = 0
        while True:
          if player == 0:
             print_grid(hgrid)
          else:
             print_grid(ygrid)
          print("Player %c  is playing now" % marks[player])
          i = read_input()
          mark(i)
          if check_win_tie():
                break
          player = (player + 1) % n_players
while True:
    clear_grid()
    set_elements()
    play()
    c = input('Play Again [Y/N] ')
    if c not in 'yY':
      break
