import { AppBar, Box, Button, IconButton, Toolbar, Typography, colors } from "@mui/material";
import { Link, useLocation } from "react-router-dom";
import LocalLibraryIcon from "@mui/icons-material/LocalLibrary";
import AddIcon from '@mui/icons-material/Add';
import SummarizeIcon from '@mui/icons-material/Summarize';
import MenuBookIcon from '@mui/icons-material/MenuBook';
import ViewListIcon from '@mui/icons-material/ViewList';

export const AppMenu = () => {
    const location = useLocation();
	const path = location.pathname;

	return (
		<Box sx={{ flexGrow: 1 }}>
			<AppBar position="static" sx={{ marginBottom: "20px", backgroundColor: colors.purple[200]}}>
				<Toolbar>
					<IconButton
						component={Link}
						to="/"
						size="large"
						edge="start"
						color="inherit"
						aria-label="school"
						sx={{ mr: 2 }}>
						<MenuBookIcon/>
					</IconButton>
					<Typography variant="h6" component="div" sx={{ mr: 5 }}>
						Books management
					</Typography>
					<Button
						variant={path.startsWith("/authors") ? "outlined" : "text"}
						to="/authors"
						component={Link}
						color="inherit"
						sx={{ mr: 5 }}
						startIcon={<LocalLibraryIcon />}>
						Authors
					</Button>
					<Button
						variant={path.startsWith("/authors/order-by-page-number") ? "outlined" : "text"}
						to="/authors/order-by-page-number"
						component={Link}
						color="inherit"
						sx={{ mr: 5 }}
						startIcon={<ViewListIcon />}>
						Authors With Average Book Length
					</Button> 
				</Toolbar>
			</AppBar>
		</Box>
	)
}