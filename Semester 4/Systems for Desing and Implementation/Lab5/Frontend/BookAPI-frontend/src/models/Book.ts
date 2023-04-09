import { BookAuthor } from "./BookAuthor";
import { Genre } from "./Genre";

export interface Book{
    id: number;
    title: string;
    description: string;
    year: number;
    pages: number;
    price: number;
    genreId: number;
    genre: Genre;
    bookAuthors: BookAuthor[];
}