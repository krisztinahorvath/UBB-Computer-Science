import {
	Autocomplete,
	Button,
	Card,
	CardActions,
	CardContent,
	IconButton,
	TextField,
} from "@mui/material";
import { Container } from "@mui/system";
import { useCallback, useEffect, useState } from "react";
import { Link, useNavigate, useParams } from "react-router-dom";
import { BACKEND_URL } from "../../constants";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import axios from "axios";
import { debounce } from "lodash";
import { Author } from "../../models/Author";

export const AddAuthor = () => {
	const navigate = useNavigate();

	const [author, setAuthor] = useState<Author>({
        name: "",
        yearOfBirth: 0,
        address: "",
        email: "",
        phoneNumber: "",
    });


	const [authorNames, setAuthorNames] = useState<Author[]>([]);

	const fetchSuggestions = async (query: string) => {
		try {
			const response = await axios.get<Author[]>(
				`${BACKEND_URL}/authors/autocomplete?query=${query}&pageNumber=1&pageSize=100`
			);
			const data = await response.data;
			setAuthorNames(data);
		} catch (error) {
			console.error("Error fetching suggestions:", error);
		}
	};

	const debouncedFetchSuggestions = useCallback(debounce(fetchSuggestions, 500), []);

	useEffect(() => {
		return () => {
			debouncedFetchSuggestions.cancel();
		};
	}, [debouncedFetchSuggestions]);

	const addAuthor = async (event: { preventDefault: () => void }) => {
		event.preventDefault();
		try {
			await axios.post(`${BACKEND_URL}/authors/`, author);
			navigate("/author");
		} catch (error) {
			console.log(error);
		}
	};

	const handleInputChange = (event: any, value: any, reason: any) => {
		console.log("input", value, reason);

		if (reason === "input") {
			debouncedFetchSuggestions(value);
		}
	};

	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/authors`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<form onSubmit={addAuthor}>
                    <Autocomplete
							id="name"
							options={authorNames}
							getOptionLabel={(option) => `${option.name}`}
							renderInput={(params) => <TextField {...params} label="Name" variant="outlined" />}
							filterOptions={(x) => x}
							onInputChange={handleInputChange}
							onChange={(event, value) => {
								if (value) {
									console.log(value);
									setAuthor({ ...author, name: value.name });
								}
							}}
						/>

						<TextField
                            id="yearOfBirth"
                            label="Year of Birth"
                            variant="outlined"
                            onChange={(event) => setAuthor({...author, yearOfBirth: parseInt(event.target.value)})}
						/>
						<TextField
                            id="address"
                            label="Address"
                            variant="outlined"
                            onChange={(event) => setAuthor({...author, address: event.target.value})}
						/>
                        <TextField 
                            id="email"
                            label="Email"
                            variant="outlined"
                            onChange={(event) => setAuthor({...author, email: event.target.value})}
                        />
                        <TextField 
                                id="phoneNumber"
                                label="Phone Number"
                                variant="outlined"
                                onChange={(event) => setAuthor({...author, phoneNumber: event.target.value})}
                        />

						<Button type="submit">Add Author</Button>
					</form>
				</CardContent>
				<CardActions></CardActions>
			</Card>
		</Container>
	);
};