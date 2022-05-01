public class Main {
    public static void main(String[] args) {
        //FamilyMember.SetMode("no");
        //FamilyMember.SetMode("natural");
        FamilyMember.SetMode("alternative");

        FamilyMember Babcia = new FamilyMember("Teresa", 79, 167);

            FamilyMember Tata = new FamilyMember("Wojciech", 52, 180);
            Babcia.AddChild(Tata);

            Tata.AddChild(new FamilyMember("Kacper",20,175));
            Tata.AddChild(new FamilyMember("Brat",20,100));
            Tata.AddChild(new FamilyMember("Maja",21,166));
            Tata.AddChild(new FamilyMember("Ktoś",30,170));
            FamilyMember Michal = new FamilyMember("Michal",23,179);
            Tata.AddChild(Michal);
                Michal.AddChild(new FamilyMember("Franek",5,114));
                Michal.AddChild(new FamilyMember("Zuzia",1,50));
                Michal.AddChild(new FamilyMember("Dominik",7,114));
                Michal.AddChild(new FamilyMember("Dominik",6,114));

        Babcia.AddChild(new FamilyMember("Krystyna", 62, 168));




        Babcia.PrintFamily();
    }
}
