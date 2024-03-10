from functools import cmp_to_key 

ELEVATOR_WEIGHT = 2000 
HUMAN_WEIGHT = 60 
DISTANCE_BETWEEN_FLOORS = 3
ACCELERATION_GRAVITY = 10 

n, cur_level = map(int, input().split( )) 
rq = [] 
for i in range(n): 
    arr = list(map(int, input().split(" ")))
    rq.append(arr) 
left = [] 
right = [] 
for i in range(n): 
    if (rq[i][0] >= cur_level): 
        right.append([i+1, 1])  
    else: 
        left.append([i+1, 1]) 
last = cur_level 
ans = 0 
num = 0 

def cmp(A, B): 
    return rq[A[0]-1][(A[1]+1)%2] - rq[B[0]-1][(B[1]+1)%2] 

while right: 
    right.sort(key = cmp_to_key(cmp)) 
    rq_num = right[0][0]
    if right[0][1] == 1: 
        ans += (num * HUMAN_WEIGHT + ELEVATOR_WEIGHT) * ACCELERATION_GRAVITY * abs(last - rq[rq_num-1][0]) * DISTANCE_BETWEEN_FLOORS
        last = rq[rq_num-1][0] 
        num += 1 
        if rq[rq_num-1][1] >= last: 
            right.append([rq_num, 0])
        else: 
            left.append([rq_num, 0]) 
    elif right[0][1] == 0: 
        ans += (num * HUMAN_WEIGHT + ELEVATOR_WEIGHT) * ACCELERATION_GRAVITY * abs(last - rq[rq_num-1][1]) * DISTANCE_BETWEEN_FLOORS
        last = rq[rq_num-1][1] 
        num -= 1 
    right.pop(0) 

while left: 
    left.sort(key = cmp_to_key(cmp)) 
    rq_num = left[0][0]
    if left[0][1] == 1: 
        ans += (num * HUMAN_WEIGHT + ELEVATOR_WEIGHT) * ACCELERATION_GRAVITY * abs(last - rq[rq_num-1][0]) * DISTANCE_BETWEEN_FLOORS
        last = rq[rq_num-1][0] 
        num += 1 
        if rq[rq_num-1][1] <= last: 
            left.append([rq_num, 0])
        else: 
            right.append([rq_num, 0]) 
    elif left[0][1] == 0: 
        ans += (num * HUMAN_WEIGHT + ELEVATOR_WEIGHT) * ACCELERATION_GRAVITY * abs(last - rq[rq_num-1][1]) * DISTANCE_BETWEEN_FLOORS
        last = rq[rq_num-1][1] 
        num -= 1 
    left.pop(0) 

while right: 
    right.sort(key = cmp_to_key(cmp)) 
    rq_num = right[0][0]
    if right[0][1] == 1: 
        ans += (num * HUMAN_WEIGHT + ELEVATOR_WEIGHT) * ACCELERATION_GRAVITY * abs(last - rq[rq_num-1][0]) * DISTANCE_BETWEEN_FLOORS
        last = rq[rq_num-1][0] 
        num += 1 
    elif right[0][1] == 0: 
        ans += (num * HUMAN_WEIGHT + ELEVATOR_WEIGHT) * ACCELERATION_GRAVITY * abs(last - rq[rq_num-1][1]) * DISTANCE_BETWEEN_FLOORS
        last = rq[rq_num-1][1] 
        num -= 1 
    right.pop(0) 

print(ans)
