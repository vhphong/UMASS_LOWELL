# combination funtion
def comb(n, m)
    p (0...n).to_a.combination(m).to_a
end

# getting first user input
puts "Enter the frist number"
N = gets.to_i

# getting second user input
puts "Enter the second number"
K  = gets.to_i

# putting inputs in funtion to do combination
comb(N, K)
