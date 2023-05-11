import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { DocumentBrowserComponent } from './document-browser/document-browser.component';
import { DocumentHomeComponent } from './document-home/document-home.component';
import { DocumentRemoveComponent } from './document-remove/document-remove.component';
import { DocumentUpdateComponent } from './document-update/document-update.component';
import { DocumentAddComponent } from './document-add/document-add.component';

import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';

@NgModule({
  declarations: [
    AppComponent,
    DocumentBrowserComponent,
    DocumentHomeComponent,
    DocumentRemoveComponent,
    DocumentUpdateComponent,
    DocumentAddComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    FormsModule,
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
