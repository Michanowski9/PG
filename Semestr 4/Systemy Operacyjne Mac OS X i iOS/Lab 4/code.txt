import Foundation

enum Type{
    case Rock
    case Pop
    case Metal
}

class Author: Equatable {
    var type: String{""}
    var scenicName: String
    var yearOfCreation: Int
    var musicType: Type

    init(scenicName: String, yearOfCreation: Int, musicType: Type){
        self.scenicName = scenicName
        self.yearOfCreation = yearOfCreation
        self.musicType = musicType
    }

    static func == (lhs: Author, rhs: Author) -> Bool {
        if lhs.scenicName != rhs.scenicName {
            return false
        }
        if lhs.yearOfCreation != rhs.yearOfCreation {
            return false
        }
        return true;
    }
}

class Band: Author{
    override var type: String{"Band"}
    var musicans: [(String, String)]

    init(scenicName: String, yearOfCreation: Int, musicans: [(String, String)], musicType: Type){
        self.musicans = musicans
        super.init(scenicName: scenicName, yearOfCreation: yearOfCreation, musicType: musicType)
    }
}

class Soloist : Author{
    override var type: String{"Musican"}
    var name: String
    var surname: String

    init(name: String, surname: String, scenicName: String, yearOfCreation: Int, musicType: Type){
        self.name = name
        self.surname = surname
        super.init(scenicName: scenicName, yearOfCreation: yearOfCreation, musicType: musicType)
    }
}

class Album {
    init(name: String, authors: [Author], year: Int, songs: [Song]){
        self.name = name
        self.authors = authors
        self.year = year
        self.songs = songs
    }
    var name: String
    var authors: [Author]
    var year: Int
    var songs: [Song]
}

struct Song {
    init(name: String, authors: [Author]){
        self.name = name
        self.authors = authors
    }
    var name: String
    var authors: [Author]
}

func printAlbum(_ album: Album){
    print("Album name: \(album.name) | Author: ", terminator: "")
    for author in album.authors {
        print("\(author.scenicName) ", terminator: "")
    }
    print ("| Year: \(album.year)")
    for song in album.songs{
        printSong(song)
    }
}

func printSong( _ song: Song){
    print("\t\tName: \"\(song.name)\" | Authors: ", terminator: "")
    for author in song.authors {
        if (author != song.authors.last) {
            print("\(author.scenicName), ",terminator: "")
        }
        else {
            print("\(author.scenicName)")
        }
    }
}

var kult = Band(scenicName: "Kult", 
                yearOfCreation: 1982, 
                musicans: [("Kazik", "Staszewski"),
                            ("Piotr", "Morawiec"),
                            ("Janusz", "Grudziński"), 
                            ("Ireneusz", "Wereński"),
                            ("Tomasz", "Goehs"),
                            ("Janusz", "Zdunek"),
                            ("Tomasz", "Glazik"),
                            ("Wojciech", "Jabłoński"),
                            ("Jarosław", "Ważny")
                            ], 
                musicType: .Rock)
var ozzy = Soloist(name: "Ozzy", surname: "Osbourne", scenicName: "Ozzy Osbourne", yearOfCreation: 1968, musicType: .Metal)
var eltonJohn = Soloist(name: "Elton", surname: "John", scenicName: "Elton John", yearOfCreation: 1962, musicType: .Pop)
 
var songs = [Song]()
songs.append(Song(name: "Celina",  authors: [kult]))
songs.append(Song(name: "Dziewczyna się bała pogrzebów",  authors: [kult]))
songs.append(Song(name: "Baranek",  authors: [kult]))
songs.append(Song(name: "Notoryczna narzeczona",  authors: [kult]))

var albums = [Album]()
albums.append(Album(name: "Tata Kazika", 
                    authors: [kult], 
                    year: 1993, 
                    songs: songs))

albums.append(Album(name: "Ordinary Man", 
                    authors: [ozzy, eltonJohn], 
                    year: 2020, 
                    songs: [Song(name: "Ordinary Man",  authors: [ozzy, eltonJohn])]))

for album in albums{
    printAlbum(album)
}
