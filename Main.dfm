object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  PixelsPerInch = 96
  TextHeight = 15
  object Label1: TLabel
    Left = 8
    Top = 27
    Width = 35
    Height = 15
    Caption = 'Target:'
  end
  object Label2: TLabel
    Left = 8
    Top = 96
    Width = 42
    Height = 15
    Caption = 'FS Type:'
  end
  object Label3: TLabel
    Left = 8
    Top = 117
    Width = 87
    Height = 15
    Caption = 'Bytes per Sector:'
  end
  object Label4: TLabel
    Left = 8
    Top = 138
    Width = 101
    Height = 15
    Caption = 'Sectors per Cluster:'
  end
  object Label5: TLabel
    Left = 8
    Top = 159
    Width = 91
    Height = 15
    Caption = 'Bytes per Cluster:'
  end
  object Label6: TLabel
    Left = 8
    Top = 180
    Width = 73
    Height = 15
    Caption = 'Total Clusters:'
  end
  object Label7: TLabel
    Left = 128
    Top = 96
    Width = 5
    Height = 15
    Caption = '-'
  end
  object Label8: TLabel
    Left = 128
    Top = 117
    Width = 5
    Height = 15
    Caption = '-'
  end
  object Label9: TLabel
    Left = 128
    Top = 138
    Width = 5
    Height = 15
    Caption = '-'
  end
  object Label10: TLabel
    Left = 128
    Top = 159
    Width = 5
    Height = 15
    Caption = '-'
  end
  object Label11: TLabel
    Left = 128
    Top = 180
    Width = 5
    Height = 15
    Caption = '-'
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 248
    Top = 8
    Width = 368
    Height = 401
    Header.AutoSizeIndex = 0
    TabOrder = 0
    OnAddToSelection = VirtualStringTree1AddToSelection
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'Signature'
      end
      item
        Position = 1
        Text = 'Cluster'
      end>
  end
  object Edit1: TEdit
    Left = 8
    Top = 48
    Width = 81
    Height = 23
    TabOrder = 1
    Text = '\\.\E:'
  end
  object Button1: TButton
    Left = 103
    Top = 48
    Width = 105
    Height = 23
    Caption = 'Open Target Disk'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 408
    Width = 75
    Height = 25
    Caption = 'Exit'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 24
    Top = 216
    Width = 161
    Height = 33
    Caption = 'Start Signature Search'
    Enabled = False
    TabOrder = 4
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 24
    Top = 296
    Width = 161
    Height = 33
    Caption = 'Stop Signature Search'
    Enabled = False
    TabOrder = 5
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 8
    Top = 352
    Width = 87
    Height = 25
    Caption = 'Clear Table'
    TabOrder = 6
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 110
    Top = 352
    Width = 98
    Height = 25
    Caption = 'Delete Selected'
    Enabled = False
    TabOrder = 7
    OnClick = Button6Click
  end
  object CheckBox1: TCheckBox
    Left = 24
    Top = 264
    Width = 161
    Height = 17
    Caption = 'Ignore Empty Clusters'
    Checked = True
    State = cbChecked
    TabOrder = 8
  end
end
