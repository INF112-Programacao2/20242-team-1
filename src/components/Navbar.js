import React from "react";
import { Link } from "react-router-dom";
import Box from '@mui/material/Box';
import List from '@mui/material/List';
import ListItem from '@mui/material/ListItem';
import ListItemButton from '@mui/material/ListItemButton';
import ListItemIcon from '@mui/material/ListItemIcon';
import ListItemText from '@mui/material/ListItemText';
import SignalCellularAltIcon from '@mui/icons-material/SignalCellularAlt';
import SettingsIcon from '@mui/icons-material/Settings';
import StyleIcon from '@mui/icons-material/Style';
function Navbar() {
    return (
        <Box sx={{ width: '100%', bgcolor: 'background.paper' }}>
            <nav aria-label="Barra de Navegação">
                <List sx={{ display: 'inline-flex' }}>
                    <ListItem disablePadding>
                        <Link to='/pad' style={{ textDecoration: 'none', color:"#000c" }}>
                            <ListItemButton>
                                <ListItemIcon>
                                    <StyleIcon />
                                </ListItemIcon>
                                <ListItemText primary="Baralhos" />
                            </ListItemButton>
                        </Link>
                    </ListItem>
                    <ListItem disablePadding>
                        <Link to='/' style={{ textDecoration: 'none', color:"#000c" }}>
                            <ListItemButton>
                                <ListItemIcon>
                                    <SettingsIcon />
                                </ListItemIcon>
                                <ListItemText primary="Configurações" />
                            </ListItemButton>
                        </Link>
                    </ListItem>
                    <ListItem disablePadding>
                        <Link to='/' style={{ textDecoration: 'none', color:"#000c" }}>
                            <ListItemButton>
                                <ListItemIcon>
                                    <SignalCellularAltIcon />
                                </ListItemIcon>
                                <ListItemText primary="Estatísticas" />
                            </ListItemButton>
                        </Link>
                    </ListItem>
                </List>
            </nav>
        </Box>
    );
}

export default Navbar;