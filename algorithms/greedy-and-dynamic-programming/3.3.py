def main():
    n = int(input())
    L = input()
    R = input()
    print(count_diff(L, R, n))

def count_diff(L, R, n):
    if R == L:
        return 2 * n
    else:
        answer = 0
        for i in range(n):
            l_digit = int(L[i])
            r_digit = int(R[i])
            if l_digit == r_digit:
                answer += 2
            elif l_digit + 1 == r_digit:
                answer += 1
                for j in range(i + 1, n):
                    if L[j] == '9' and R[j] == '0':
                        answer += 1
                    else:
                        break
                break
            else:
                break
        return answer

main()