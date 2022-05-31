using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace PT_Lab3
{
    public class Serialization
    {
        string fileName = "";
        string filePath = "";
        public Serialization(string fileName)
        {
            this.fileName = fileName;
            this.filePath = Path.Combine(Directory.GetCurrentDirectory(), fileName);
        }
        public List<Car> Deserialize()
        {
            var result = new List<Car>();
            var xmlSerializer = new XmlSerializer(
                    typeof(List<Car>),
                    new XmlRootAttribute("cars")
                );
            using (var reader = new FileStream(this.filePath, FileMode.Open))
            {
                result = (List<Car>)xmlSerializer.Deserialize(reader);
            }
            return result;
        }
        public void Serialize(List<Car> collection)
        {
            var xmlSerializer = new XmlSerializer(
                    typeof(List<Car>),
                    new XmlRootAttribute("cars")
                );
            using (var writer = new StreamWriter(this.filePath))
            {
                xmlSerializer.Serialize(writer, collection);
            }
        }

    }
}
