//Zadanie 1.1
	func minValue(_ a:Int, _ b:Int) -> Int{
	    if(a > b){
	        return b;
	    }
	    return a;
	}

	print(minValue(2,5));
	print(minValue(5,12));
	print(minValue(9,6));

//Zadanie 1.2
    func lastDigit(_ input:Int) -> Int{
        return input % 10;
    }

    print(lastDigit(123));

//Zadanie 1.3
        func divides(_ a:Int, _ b:Int) -> Bool{
        if(a%b == 0){
            return true
        }
        return false
    }

    print(divides(7, 3));
    print(divides(8, 4));

    func countDivisors(_ a:Int) -> Int {
        var result = 0
        for i in 1...a {
            if(divides(a,i)){
                result+=1
            }
        }
        return result
    }

    print(countDivisors(1))
    print(countDivisors(10))
    print(countDivisors(12))

    func isPrime(_ a:Int) -> Bool {
        return countDivisors(a) == 2
    }

    print(isPrime(3));
    print(isPrime(8));
    print(isPrime(13));


//Zadanie 2.1
    func smartBart(_ n:Int,_ a:()->()) -> (){
        for i in 1...n {
            a()
        }
    }
    smartBart(5,{print("I will pass this course with best mark, because Swift is great!")})

//Zadanie 2.2
    let numbers = [10, 16, 18, 30, 38, 40, 44, 50]

    print(numbers.filter{$0 % 4 == 0})

//Zadanie 2.3
    let numbers = [10, 16, 18, 30, 38, 40, 44, 50]

    print(numbers.reduce(0){max($0, $1)})

//Zadanie 2.4
    var strings = ["Gdansk", "University", "of", "Technology"]
    print(strings.reduce(""){$0 + " " + $1})

//Zadanie 2.5
    let numbers = [1, 2 ,3 ,4, 5, 6]
    print(numbers.filter{$0 % 2 == 1}.map{$0*$0}.reduce(0){$0+$1})

//Zadanie 3.1
    func minmax(_ a:Int, _ b:Int) -> (Int,Int){
        return (min(a,b),max(a,b));
    }

    print(minmax(5,4));

//Zadanie 3.2
    var stringsArray = ["gdansk", "university", "gdansk", "university", "university", "of",  "technology", "technology", "gdansk", "gdansk"]
    var countedStrings: [(String, Int)] = []

    for str in stringsArray {
        if countedStrings.contains(where:{$0.0 == str}) {
            continue
        }
        var temp = 0;
        for i in 0..<stringsArray.count {
            if str == stringsArray[i] {
                temp += 1;
            }
        }
        countedStrings.append((str, temp))
    }
    print(countedStrings)

//Zadanie 4.1
    enum Day:Int{
        case Monday
        case Tuesday
        case Wednesday
        case Thursday
        case Friday
        case Saturday
        case Sunday

        func emoji() -> String {
            switch self {
                case .Monday:
                    return "🏆"
                case .Tuesday:
                    return "🎉"
                case .Wednesday:
                    return "🙌"
                case .Thursday:
                    return "🍾"
                case .Friday:
                    return "👨‍💻"
                case .Saturday:
                    return "🤩"
                case .Sunday:
                    return "😍"
            }
        }
    }

    print(Day.Sunday.emoji())