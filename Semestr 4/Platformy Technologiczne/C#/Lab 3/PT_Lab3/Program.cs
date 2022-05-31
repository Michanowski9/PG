using PT_Lab3;
using System.Xml.Linq;
using System.Xml.XPath;

var myCars = CreateList();
Exercise1_Linq();
Exercise2_Serialization();
Exercise3_XPath();
Exercise4_XmlFromLinq();
Exercise5_Xhtml();
Exercise6_Modification();



List<Car> CreateList()
{
    return new List<Car>(){
                new Car("E250", new Engine(1.8, 204, "CGI"), 2009),
                new Car("E350", new Engine(3.5, 292, "CGI"), 2009),
                new Car("A6", new Engine(2.5, 187, "FSI"), 2012),
                new Car("A6", new Engine(2.8, 220, "FSI"), 2012),
                new Car("A6", new Engine(3.0, 295, "TFSI"), 2012),
                new Car("A6", new Engine(2.0, 175, "TDI"), 2011),
                new Car("A6", new Engine(3.0, 309, "TDI"), 2011),
                new Car("S6", new Engine(4.0, 414, "TFSI"), 2012),
            new Car("S8", new Engine(4.0, 513, "TFSI"), 2012)
            };
}
void Exercise1_Linq()
{
    Console.WriteLine("\tEXERCISE 1 - LINQ");
    var annonymousCarsQuery = myCars
        .Where(s => s.model.Equals("A6"))
        .Select(car =>
            new
            {
                engineType = String.Compare(car.motor.model, "TDI") == 0 ? "diesel" : "petrol",
                hppl = car.motor.horsePower / car.motor.displacement,
            });

    var groupedQuery = annonymousCarsQuery
        .GroupBy(elem => elem.engineType)
        .Select(elem => $"{elem.First().engineType}: {elem.Average(s => s.hppl).ToString()}");


    foreach (var elem in annonymousCarsQuery)
    {
        Console.WriteLine(elem.ToString());
    }
    Console.WriteLine();

    foreach (var elem in groupedQuery)
    {
        Console.WriteLine(elem);
    }
    Console.WriteLine();
}
void Exercise2_Serialization()
{
    Console.WriteLine("\tEXERCISE 2 - SERIALIZATION");

    var serializator = new Serialization("CarsCollection.xml");
    serializator.Serialize(myCars);

    var deserializedCollection = serializator.Deserialize();
    Console.WriteLine("deserialized list: ");
    foreach (var elem in deserializedCollection)
    {
        Console.WriteLine(elem.model);
    }
    Console.WriteLine();
}
void Exercise3_XPath()
{
    Console.WriteLine("\tEXERCISE 3 - XPath");
    var rootNode = XElement.Load("CarsCollection.xml");
    var avgHP = (double)rootNode.XPathEvaluate("sum(//car/engine[@model!=\"TDI\"]/horsePower) div count(//car/engine[@model!=\"TDI\"]/horsePower)");
    Console.WriteLine("Średnia: " + avgHP);

    var models = rootNode.XPathSelectElements("//car[not(following-sibling::car/model = model)]/model");
    foreach(var model in models)
    {
        Console.WriteLine(model);
    }
}
void Exercise4_XmlFromLinq()
{
    Console.WriteLine("\tEXERCISE 4 - XML FROM LINQ");
    var nodes = myCars
        .Select(n =>
        new XElement("car",
            new XElement("model", n.model),
            new XElement("engine",
                new XAttribute("model", n.motor.model),
                new XElement("displacement", n.motor.displacement),
                new XElement("horsePower", n.motor.horsePower)),
            new XElement("year", n.year)
            ));
    var rootNode = new XElement("cars", nodes); //create a root node to contain the query results
    rootNode.Save("CarsFromLinq.xml");
}
void Exercise5_Xhtml()
{
    Console.WriteLine("\tEXERCISE 5 - XHTML");
    var style1 = new XAttribute("style", "border: 2px solid black");
    var style2 = new XAttribute("style", "border: 2px double black");

    var rows = myCars
                .Select(car =>
                new XElement("tr", style1,
                    new XElement("td", style2, car.model),
                    new XElement("td", style2, car.motor.model),
                    new XElement("td", style2, car.motor.displacement),
                    new XElement("td", style2, car.motor.horsePower),
                    new XElement("td", style2, car.year)));
    var table = new XElement("table", style2, rows);

    var template = XElement.Load("template.html");
    var body = template.Element("{http://www.w3.org/1999/xhtml}body");
    body.Add(table);

    template.Save("linqToXhtml.html");
}
void Exercise6_Modification()
{
    Console.WriteLine("\tEXERCISE 6 - MODIFICATION");

    var result = XElement.Load("CarsCollection.xml");
    foreach (var car in result.Elements())
    {
        foreach (var attr in car.Elements())
        {
            if (attr.Name == "engine")
            {
                foreach (var engineElement in attr.Elements())
                {
                    if (engineElement.Name == "horsePower")
                    {
                        engineElement.Name = "hp";
                    }
                }
            }
            else if (attr.Name == "model")
            {
                var year = car.Element("year");
                year.Remove();

                var attribute = new XAttribute("year", year.Value);
                attr.Add(attribute);
            }
        }
    }
    result.Save("CarsCollection2.xml");
}