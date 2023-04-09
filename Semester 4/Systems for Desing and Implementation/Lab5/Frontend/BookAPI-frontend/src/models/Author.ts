import { BookAuthor } from "./BookAuthor";

export interface Author{
    id: number;
    name: string;
    yearOfBirth: number;
    address: string;
    email: string;
    phoneNumber: string;
    bookAuthors: BookAuthor[];
}