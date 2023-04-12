import { Book } from "./Book";

export interface AuthorWithBookDTO{
    id: number;
    name: string;
    yearOfBirth: number;
    address: string;
    email: string;
    phoneNumber: string;
    books: Book[];
}