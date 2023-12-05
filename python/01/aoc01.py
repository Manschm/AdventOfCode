sum = 0
with open('input.txt') as f:
    for line in f:
        nums = []
        for c in line:
            if c in '0123456789':
                nums.append(c)
        sum += int(nums[0] + nums[-1])

print(sum)
