import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DocumentUpdateComponent } from './document-update.component';

describe('DocumentUpdateComponent', () => {
  let component: DocumentUpdateComponent;
  let fixture: ComponentFixture<DocumentUpdateComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [DocumentUpdateComponent]
    });
    fixture = TestBed.createComponent(DocumentUpdateComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
