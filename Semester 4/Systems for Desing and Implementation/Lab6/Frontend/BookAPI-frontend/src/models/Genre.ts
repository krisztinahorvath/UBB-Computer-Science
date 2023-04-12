import { Book } from "./Book";

export interface Genre{
    id: number;
    name: string;
    description: string;
    subgenre: string;
    countryOfOrigin: string;
    genreRating: number;
    bookList: Book[];
}