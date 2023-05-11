import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { DocumentHomeComponent } from './document-home/document-home.component';
import { DocumentBrowserComponent } from './document-browser/document-browser.component';
import { DocumentAddComponent } from './document-add/document-add.component';
import { DocumentRemoveComponent } from './document-remove/document-remove.component';
import { DocumentUpdateComponent } from './document-update/document-update.component';

const routes: Routes = [
    {path: '', redirectTo: '/home', pathMatch: 'full'},
    {path: 'home', component: DocumentHomeComponent},
    {path: 'browse', component: DocumentBrowserComponent},
    {path: 'add', component: DocumentAddComponent},
    {path: 'delete', component: DocumentRemoveComponent},
    {path: 'edit', component: DocumentUpdateComponent},

];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
