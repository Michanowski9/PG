Zadanie 1.1:

	var first = 5
	var second = 10

	print("\(first) + \(second) = \(first+second)")

Zadanie 1.2:

	var input = "Gdansk University of Technology"
	var output = ""

	for char in input {
		if char == "n" {
			output = "\(output)⭐️" 
		}
		else {
			output = "\(output)\(char)" 
		}
	}
	print(output)

Zadanie 1.3:

	var input = "Michał Soja"
	var output = ""

	for char in input {
		output="\(char)\(output)"
	}
	print(output)
	
Zadanie 2.1:

	for _ in 1...11 {
		print("I will pass this course with best mark, because Swift is great!")
	}

Zadanie 2.2:

	var n = 5
	for i in 1...n {
		print("\(i*i)")
	}

Zadanie 2.3:

	var n = 5
	for i in 1...n {
		for j in 1...n-1 {
			print("@", terminator: "")
		}
		print("@")
	}
	
Zadanie 3.1:

	var numbers = [5, 10, 20, 15, 80, 13]
	var max = 0

	for i in numbers {
		if i > max {
			max = i
		}
	}
	print(max)
	
Zadanie 3.2:

	var numbers = [5, 10, 20, 15, 80, 13]

	for i in numbers.reversed() {
		print("\(i) ", terminator: "") 
	}
	
Zadanie 3.3:

	var allNumbers = [10, 20, 10, 11, 13, 20, 10, 30]
	var unique = [Int]()

	for i in allNumbers {
		if unique.isEmpty {
			unique.append(i)
		}
		else {
			if(!unique.contains(i)) {
				unique.append(i)
			}
		}
	}
	for i in unique {
		print("\(i) ", terminator: "")
	}
	
Zadanie 4.1:

	var number = 10

	var divisors = Set<Int>()
	for i in 1...number {
		if number % i == 0 {
			divisors.insert(i)
		}
	}

	print("divisors = \(divisors.sorted())")
	
Zadanie 5.1:

	var flights: [[String: String]] = [
		[
			"flightNumber" : "AA8025",
			"destination" : "Copenhagen"
		],
		[
			"flightNumber" : "BA1442",
			"destination" : "New York"
		],
		[
			"flightNumber" : "BD6741",
			"destination" : "Barcelona"
		]
	]

	var flightNumbers = [String]();
	for flight in flights {
		for (key, value) in flight {
			if key == "flightNumber" {
				flightNumbers.append(value)
			}
		}
	}
	print("\(flightNumbers)")
	
Zadanie 5.2:

	var names = ["Hommer","Lisa","Bart"]
	var fullName = [[String: String]]()
	
	for name in names {
		fullName.append(["lastName" : "Simpson" , "firstName" : name ])
	}
	
	print("fullName = \(fullName)")
