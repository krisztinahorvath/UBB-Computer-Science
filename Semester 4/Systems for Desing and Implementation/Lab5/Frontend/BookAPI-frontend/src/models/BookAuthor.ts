import { Author } from "./Author";
import { Book } from "./Book";

export interface BookAuthor{
    bookId: number;
    book: Book;

    authorId: number;
    author: Author;

    bookRating: number;
    authorRating: number;
}