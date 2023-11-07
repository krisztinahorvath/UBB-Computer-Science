package com.example.recipejournal.screens

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material.icons.filled.Edit
import androidx.compose.material3.Card
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavHostController
import androidx.navigation.compose.currentBackStackEntryAsState
import com.example.recipejournal.viewmodels.RecipeViewModel
import com.example.recipejournal.viewmodels.SelectedRecipeViewModel

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun RecipeDetails(
    viewModel: RecipeViewModel,
    selectedRecipeViewModel: SelectedRecipeViewModel,
    navController: NavHostController
) {
    val selectedRecipeId = selectedRecipeViewModel.selectedRecipeId
    val recipe = viewModel.getRecipeById(selectedRecipeId)

    val boldTextStyle = androidx.compose.ui.text.TextStyle(
        fontSize = 20.sp,
        fontWeight = FontWeight.Bold
    )

    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(20.dp)
    ) {
        TopAppBar(
            title = { Text("Recipe Details") },
            navigationIcon = {
                IconButton(
                    onClick = {
                        navController.popBackStack()
                    }
                ) {
                    Icon(imageVector = Icons.Default.ArrowBack, contentDescription = "Back", modifier = Modifier.size(35.dp))
                }
            },
            actions = {
                IconButton(
                    onClick = { navController.navigate(RecipeNavigation.RECIPE_UPDATE) }
                ) {
                    Icon(imageVector = Icons.Default.Edit, contentDescription = "Update", modifier = Modifier.size(35.dp))
                }
            }
        )

        // recipe name
        Text(
            text = recipe.name,
            fontSize = 30.sp,
            fontWeight = FontWeight.Bold,
            modifier = Modifier.padding(bottom = 16.dp)
        )

        // card containing preparation time and servings
        Surface(
            modifier = Modifier.fillMaxWidth(),
            color = Color.White,
        ) {
            Card(
                modifier = Modifier.padding(8.dp)
            ) {
                Column(
                    modifier = Modifier.padding(16.dp)
                ) {
                    Text("Preparation Time: ${recipe.time} minutes")
                    Text("Servings: ${recipe.servings}")
                }
            }
        }

        // list of ingredients as bullet points
        Spacer(modifier = Modifier.height(16.dp))
        Text(
            text = "Ingredients:",
            style = boldTextStyle
        )
        recipe.ingredients.split(",").forEach { ingredient ->
            Row(
                modifier = Modifier.padding(vertical = 4.dp),
                verticalAlignment = Alignment.CenterVertically
            ) {
                Text("\u2022", fontSize = 16.sp, fontWeight = FontWeight.Bold)
                Text(
                    text = if (ingredient.trim().isNotEmpty()) {
                        ingredient.trim()
                    } else {
                        "Ingredients not available"
                    },
                    style = androidx.compose.ui.text.TextStyle(fontSize = 16.sp),
                    modifier = Modifier.padding(start = 8.dp)
                )
            }
        }

        // directions
        Spacer(modifier = Modifier.height(16.dp))
        Text(
            text = "Directions:",
            style = boldTextStyle
        )
        Text(
            text = if (recipe.directions.isNotEmpty()) {
                recipe.directions
            } else {
                "Directions not available"
            },
            style = androidx.compose.ui.text.TextStyle(fontSize = 16.sp)
        )
    }
}

