import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DocumentAddComponent } from './document-add.component';

describe('DocumentAddComponent', () => {
  let component: DocumentAddComponent;
  let fixture: ComponentFixture<DocumentAddComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [DocumentAddComponent]
    });
    fixture = TestBed.createComponent(DocumentAddComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
