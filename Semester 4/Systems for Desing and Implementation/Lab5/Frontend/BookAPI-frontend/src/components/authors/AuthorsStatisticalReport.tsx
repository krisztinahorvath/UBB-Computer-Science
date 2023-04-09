import { useEffect, useState } from "react";
import { Container, Table, TableContainer, TableHead, TableRow, TableCell, TableBody, colors, Paper } from "@mui/material";
import { BACKEND_URL } from "../../constants";


interface AuthorAvgBookLengthDTO{
    id: number;
    name: string;
    yearOfBirth: number;
    address: string;
    email: string;
    phoneNumber: string;
    avgPages: number;
}

export const AuthorWithAvgBookLength = () => {
    const [loading, setLoading] = useState(false);
    const [authors, setAuthors] = useState([])

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/authors/get/orderedBooks`)
        .then(response => response.json())
        .then(data => { setAuthors(data); setLoading(false); });
    } , []);

    return (
      <Container>
         <h2 style={{textAlign: "left", marginLeft: "12px"}}>Authors with their average book length</h2>
         {!loading && authors.length === 0 && <div>No authors in the list</div>}
         {!loading &&
            authors.length > 0 && (
                // set the table background color to white and the text color to black
                <TableContainer component={Paper}>
                    <Table sx={{ minWidth: 600}} aria-label="simple table">
                        <TableHead>
                            <TableRow>
                                <TableCell align="center">#</TableCell>
                                <TableCell align="center">Name</TableCell>
                                <TableCell align="center">Year of Birth</TableCell>
                                <TableCell align="center">Address</TableCell>
                                <TableCell align="center">Email</TableCell>
                                <TableCell align="center">Phone Number</TableCell>
                                <TableCell align="center">Average Book Length</TableCell>
                            </TableRow>
                        </TableHead>
                        
                        <TableBody>
                        {authors.map((author: AuthorAvgBookLengthDTO, index) => (
                            <TableRow key={author.id}>
                                <TableCell align="center" component="th" scope="row">{index + 1}</TableCell>
                                <TableCell align="center" component="th" scope="row">{author.name}</TableCell>
                                <TableCell align="center">{author.yearOfBirth}</TableCell>
                                <TableCell align="center">{author.address}</TableCell>
                                <TableCell align="center">{author.email}</TableCell>
                                <TableCell align="center">{author.phoneNumber}</TableCell>
                                <TableCell align="center">{author.avgPages}</TableCell>
                            </TableRow>
                        ))}
                        </TableBody>
                    </Table>
                </TableContainer>
            )
            } 
      </Container>
    )
  }